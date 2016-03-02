
#include "skybox_renderer.hpp"

#include "camera.hpp"
#include "loader.hpp"
#include "display_manager.hpp"

#include <vector>
#include <cmath>

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

constexpr const char* const night_texture_files[] = {
        "nightRight",
        "nightLeft",
        "nightTop",
        "nightBottom",
        "nightBack",
        "nightFront"
};

}

namespace jac {

skybox_renderer::skybox_renderer(loader& loader, const glm::mat4& matrix)
    : cube{loader.load_to_vao(std::vector<float>(std::begin(VERTICES),
                                                 std::end(VERTICES)), 3)},
      texture_id{loader.load_cube_map(std::vector<std::string>(std::begin(texture_files),
                                                               std::end(texture_files)))},
      night_texture_id{loader.load_cube_map(std::vector<std::string>(std::begin(night_texture_files),
                                                                     std::end(night_texture_files)))}
{
    shader.start();
    shader.connect_texture_units();
    shader.load_projection_matrix(matrix);
    shader.stop();
}

void skybox_renderer::render(const camera& cam, float r, float g, float b)
{
    shader.start();
    shader.load_view_matrix(cam);
    shader.load_fog_colour(r, g, b);
    glBindVertexArray(cube.vao_id);
    glEnableVertexAttribArray(0);
    bind_textures();
    glDrawArrays(GL_TRIANGLES, 0, cube.vertex_count);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
}


void skybox_renderer::bind_textures()
{
    time += get_frame_time_seconds().count() * 1000;
    time = std::fmod(time, 24000);
    GLuint texture1;
    GLuint texture2;
    float blendFactor;
    if(time >= 0 && time < 5000){
        texture1 = night_texture_id;
        texture2 = night_texture_id;
        blendFactor = (time - 0)/(5000 - 0);
    }else if(time >= 5000 && time < 8000){
        texture1 = night_texture_id;
        texture2 = texture_id;
        blendFactor = (time - 5000)/(8000 - 5000);
    }else if(time >= 8000 && time < 21000){
        texture1 = texture_id;
        texture2 = texture_id;
        blendFactor = (time - 8000)/(21000 - 8000);
    }else{
        texture1 = texture_id;
        texture2 = night_texture_id;
        blendFactor = (time - 21000)/(24000 - 21000);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
    shader.load_blend_factor(blendFactor);
}


}