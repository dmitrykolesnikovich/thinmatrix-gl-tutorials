
#include "renderer.hpp"

#include "entity.hpp"
#include "maths.hpp"
#include "static_shader.hpp"
#include "textured_model.hpp"

#include "SDL.h"

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace {

constexpr float fov = 70; // degrees
constexpr float near_plane = 0.1f;
constexpr float far_plane = 1000.0f;

glm::mat4 create_projection_matrix()
{
    int w, h;
    SDL_GL_GetDrawableSize(SDL_GL_GetCurrentWindow(), &w, &h);
    // This is certainly easier than the Java version...
    return glm::perspectiveFov(glm::radians(fov), float(w), float(h),
                               near_plane, far_plane);
}



}

namespace jac {

struct renderer::pimpl {
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
        glm::mat4 transformation_matrix = create_transformation_matrix(
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

renderer::renderer(const static_shader& shader)
    : priv{std::make_unique<pimpl>(create_projection_matrix(), shader)}
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    shader.start();
    shader.load_projection_matrix(priv->projection_matrix);
    shader.stop();
}

renderer::renderer(renderer&&) = default;
renderer& renderer::operator=(renderer&&) = default;
renderer::~renderer() = default;

void renderer::prepare()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::render(const entity_map &entities) const
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
