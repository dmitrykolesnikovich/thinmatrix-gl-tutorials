
#include "skybox_renderer.hpp"

#include "camera.hpp"
#include "loader.hpp"

#include <vector>

namespace {

constexpr float SIZE = 500.0f;

constexpr float VERTICES[] = {
        -SIZE, SIZE, -SIZE,
        -SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, SIZE, -SIZE,
        -SIZE, SIZE, -SIZE,

        -SIZE, -SIZE, SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE, SIZE, -SIZE,
        -SIZE, SIZE, -SIZE,
        -SIZE, SIZE, SIZE,
        -SIZE, -SIZE, SIZE,

        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, SIZE,
        SIZE, SIZE, SIZE,
        SIZE, SIZE, SIZE,
        SIZE, SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,

        -SIZE, -SIZE, SIZE,
        -SIZE, SIZE, SIZE,
        SIZE, SIZE, SIZE,
        SIZE, SIZE, SIZE,
        SIZE, -SIZE, SIZE,
        -SIZE, -SIZE, SIZE,

        -SIZE, SIZE, -SIZE,
        SIZE, SIZE, -SIZE,
        SIZE, SIZE, SIZE,
        SIZE, SIZE, SIZE,
        -SIZE, SIZE, SIZE,
        -SIZE, SIZE, -SIZE,

        -SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE, SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE, SIZE,
        SIZE, -SIZE, SIZE
};

constexpr const char * const texture_files[] = {
        "right",
        "left",
        "top",
        "bottom",
        "back",
        "front"
};

}

namespace jac {

skybox_renderer::skybox_renderer(loader& loader, const glm::mat4& matrix)
    : cube{loader.load_to_vao(std::vector<float>(std::begin(VERTICES),
                                                 std::end(VERTICES)), 3)},
      texture_id{loader.load_cube_map(std::vector<std::string>(std::begin(texture_files),
                                                               std::end(texture_files)))}
{
    shader.start();
    shader.load_projection_matrix(matrix);
    shader.stop();
}

void skybox_renderer::render(const camera& cam) const
{
    shader.start();
    shader.load_view_matrix(cam);
    glBindVertexArray(cube.vao_id);
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
    glDrawArrays(GL_TRIANGLES, 0, cube.vertex_count);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
}


}