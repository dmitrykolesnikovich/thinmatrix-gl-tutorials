
#include "entity_renderer.hpp"

#include "entity.hpp"
#include "master_renderer.hpp"
#include "maths.hpp"
#include "static_shader.hpp"
#include "textured_model.hpp"

#include "SDL.h"

#include <glad/glad.h>

namespace jac {

void entity_renderer::prepare_textured_model(const jac::textured_model& model) const
{
    const auto& raw_model = model.raw;
    glBindVertexArray(raw_model.vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    const auto& texture = model.texture;
    shader.load_number_of_rows(model.texture.number_of_rows);
    if (texture.has_transparency) {
        master_renderer::disable_culling();
    }
    shader.load_fake_lighting_variable(texture.use_fake_lighting);
    shader.load_shine_variables(texture.shine_damper, texture.reflectivity);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.texture.texture_id);
}

void entity_renderer::prepare_instance(const entity& entity) const
{
    glm::mat4 transformation_matrix = maths::create_transformation_matrix(
                entity.get_position(),
                entity.get_rot_x(),
                entity.get_rot_y(),
                entity.get_rot_z(),
                entity.get_scale());
    shader.load_transformation_matrix(transformation_matrix);
    shader.load_offset(entity.get_texture_x_offset(),
                       entity.get_texture_y_offset());
}

void entity_renderer::unbind_textured_model() const
{
    master_renderer::enable_culling();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

entity_renderer::entity_renderer(const static_shader& shader,
                                 const glm::mat4& projection_matrix)
    : projection_matrix{projection_matrix},
      shader{shader}
{
    shader.start();
    shader.load_projection_matrix(projection_matrix);
    shader.stop();
}

void entity_renderer::render(const entity_map &entities) const
{
    for (const auto& entry : entities) {
        prepare_textured_model(entry.first);
        for (const auto& entity : entry.second) {
            prepare_instance(*entity);
            glDrawElements(GL_TRIANGLES, entry.first.raw.vertex_count, GL_UNSIGNED_INT, 0);
        }
        unbind_textured_model();
    }
}

}
