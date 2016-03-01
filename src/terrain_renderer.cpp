
#include "terrain_renderer.hpp"

#include "maths.hpp"
#include "terrain.hpp"
#include "textured_model.hpp"
#include "terrain_shader.hpp"

namespace jac {

terrain_renderer::terrain_renderer(const terrain_shader& shader,
                                   const glm::mat4& projection_matrix)
    : shader{shader}
{
    shader.start();
    shader.load_projection_matrix(projection_matrix);
    shader.connect_texture_units();
    shader.stop();
}

void terrain_renderer::render(const std::vector<const terrain*>& terrains) const
{
    for (const auto& terrain : terrains) {
        prepare_terrain(*terrain);
        load_model_matrix(*terrain);

        glDrawElements(GL_TRIANGLES, terrain->get_model().vertex_count,
                       GL_UNSIGNED_INT, 0);

        unbind_textured_model();
    }
}

void terrain_renderer::prepare_terrain(const terrain& terrain) const
{
    const auto& raw_model = terrain.get_model();
    glBindVertexArray(raw_model.vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    bind_textures(terrain);
    shader.load_shine_variables(1, 0);

}

void terrain_renderer::bind_textures(const terrain& terrain) const
{
    const auto& texture_pack = terrain.get_texture_pack();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_pack.background_texture.texture_id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_pack.r_texture.texture_id);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture_pack.g_texture.texture_id);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texture_pack.b_texture.texture_id);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, terrain.get_blend_map().texture_id);
}

void terrain_renderer::load_model_matrix(const terrain& terrain) const
{
    glm::mat4 transformation_matrix = maths::create_transformation_matrix(
                glm::vec3{terrain.get_x(), 0, terrain.get_z()},
                0.0f, 0.0f, 0.0f, 1.0f);
    shader.load_transformation_matrix(transformation_matrix);
}

void terrain_renderer::unbind_textured_model() const
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}


}
