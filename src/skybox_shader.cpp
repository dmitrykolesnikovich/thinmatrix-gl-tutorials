
#include "skybox_shader.hpp"

#include "display_manager.hpp"
#include "camera.hpp"
#include "maths.hpp"

#include "SDL.h"

#include <glm/gtc/matrix_transform.hpp>

constexpr char vertex_shader_source[] = "shaders/skybox_vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/skybox_fragment_shader.frag";

constexpr float rotate_speed = 1.0f;

namespace jac {

skybox_shader::skybox_shader()
    : shader_program(vertex_shader_source, fragment_shader_source)
{
    link();
}

void skybox_shader::bind_attributes()
{
    bind_attribute(0, "position");
}

void skybox_shader::get_all_uniform_locations()
{
    location_projection_matrix = get_uniform_location("projectionMatrix");
    location_view_matrix = get_uniform_location("viewMatrix");
    location_fog_colour = get_uniform_location("fogColour");
    location_cube_map = get_uniform_location("cubeMap");
    location_cube_map2 = get_uniform_location("cubeMap2");
    location_blend_factor = get_uniform_location("blendFactor");
}

void skybox_shader::load_projection_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_projection_matrix, matrix);
}

void skybox_shader::load_view_matrix(const camera& cam)
{
    auto matrix = maths::create_view_matrix(cam);
    matrix[3] = glm::vec4{0.0, 0.0, 0.0, matrix[3][3]};
    rotation += rotate_speed * get_frame_time_seconds().count();
    matrix = glm::rotate(matrix, glm::radians(rotation), {0, 1, 0});
    load_matrix(location_view_matrix, matrix);
}

void skybox_shader::load_fog_colour(float r, float g, float b) const
{
    load_vector(location_fog_colour, {r, g, b});
}

void skybox_shader::load_blend_factor(float factor) const
{
    load_float(location_blend_factor, factor);
}

void skybox_shader::connect_texture_units() const
{
    load_int(location_cube_map, 0);
    load_int(location_cube_map2, 1);
}


}