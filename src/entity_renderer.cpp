
#include "entity_renderer.hpp"

#include "entity.hpp"
#include "maths.hpp"
#include "static_shader.hpp"
#include "textured_model.hpp"

#include "SDL.h"

#include <glad/glad.h>

namespace jac {

struct entity_renderer::pimpl {
    pimpl(const glm::mat4& mat, const static_shader& shader)
        : projection_matrix{mat}, shader{shader} {}

    glm::mat4 projection_matrix;
    const static_shader& shader;

    void prepare_textured_model(const jac::textured_model& model)
    {
        const auto& raw_model = model.raw;
        glBindVertexArray(raw_model.vao_id);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        const auto& texture = model.texture;
        shader.load_shine_variables(texture.shine_damper, texture.reflectivity);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model.texture.texture_id);
    }

    void prepare_instance(const entity& entity)
    {
        glm::mat4 transformation_matrix = maths::create_transformation_matrix(
                    entity.position,
                    entity.rot_x,
                    entity.rot_y,
                    entity.rot_z,
                    entity.scale);
        shader.load_transformation_matrix(transformation_matrix);
    }

    void unbind_textured_model()
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
    }

};

entity_renderer::entity_renderer(const static_shader& shader,
                                 const glm::mat4& projection_matrix)
    : priv{std::make_unique<pimpl>(projection_matrix, shader)}
{
    shader.start();
    shader.load_projection_matrix(priv->projection_matrix);
    shader.stop();
}

entity_renderer::entity_renderer(entity_renderer&&) = default;
entity_renderer& entity_renderer::operator=(entity_renderer&&) = default;
entity_renderer::~entity_renderer() = default;


void entity_renderer::render(const entity_map &entities) const
{
    for (const auto& entry : entities) {
        priv->prepare_textured_model(entry.first);
        for (const auto& entity : entry.second) {
            priv->prepare_instance(*entity);
            glDrawElements(GL_TRIANGLES, entry.first.raw.vertex_count, GL_UNSIGNED_INT, 0);
        }
        priv->unbind_textured_model();
    }
}

}
