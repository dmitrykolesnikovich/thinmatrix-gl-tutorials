
#include "gui_renderer.hpp"

#include "gui_texture.hpp"
#include "loader.hpp"
#include "maths.hpp"

#include <glad/glad.h>

namespace jac {

namespace {

static const std::vector<float> positions{
        -1, 1, -1, -1, 1, 1, 1, -1
};

}

gui_renderer::gui_renderer(loader& loader)
    : quad{loader.load_to_vao(positions, 2)}
{}

void gui_renderer::render(const std::vector<gui_texture>& guis) const
{
    shader.start();
    glBindVertexArray(quad.vao_id);
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for (const auto& gui : guis) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gui.texture_id);
        auto matrix = maths::create_transformation_matrix(gui.position,
                                                          gui.scale);
        shader.load_transformation(matrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.vertex_count);
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
}


}
