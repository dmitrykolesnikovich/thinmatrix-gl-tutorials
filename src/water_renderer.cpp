
#include "water_renderer.hpp"

#include "loader.hpp"
#include "maths.hpp"
#include "water_frame_buffers.hpp"
#include "water_tile.hpp"

namespace jac {

water_renderer::water_renderer(jac::loader& loader, water_shader shader_,
                               const glm::mat4& projection_matrix,
                               const water_frame_buffers& fbos)
    : shader{std::move(shader_)},
      fbos{fbos}
{
    shader.start();
    shader.connect_texture_units();
    shader.load_projection_matrix(projection_matrix);
    shader.stop();
    set_up_vao(loader);
}

void water_renderer::render(const std::vector<water_tile>& water,
                            const jac::camera& camera) const
{
    prepare_render(camera);
    for (const auto& tile : water) {
        auto model_matrix = maths::create_transformation_matrix(
                {tile.x, tile.height, tile.z}, 0, 0, 0, water_tile::tile_size);
        shader.load_model_matrix(model_matrix);
        glDrawArrays(GL_TRIANGLES, 0, quad.vertex_count);
    }
    unbind();
}

void water_renderer::prepare_render(const jac::camera& camera) const
{
    shader.start();
    shader.load_view_matrix(camera);
    glBindVertexArray(quad.vao_id);
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbos.get_reflection_texture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbos.get_refraction_texture());
}

void water_renderer::unbind() const
{
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
}

void water_renderer::set_up_vao(jac::loader& loader)
{
    const std::vector<float> vertices{ -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
    quad = loader.load_to_vao(vertices, 2);
}


}