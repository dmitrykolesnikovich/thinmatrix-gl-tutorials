
#include "skybox_shader.hpp"

#include "camera.hpp"
#include "maths.hpp"

#include "SDL.h"

constexpr char vertex_shader_source[] = "shaders/skybox_vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/skybox_fragment_shader.frag";

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
}

void skybox_shader::load_projection_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_projection_matrix, matrix);
}

void skybox_shader::load_view_matrix(const camera& cam) const
{
    auto matrix = maths::create_view_matrix(cam);
    matrix[3] = glm::vec4{0.0, 0.0, 0.0, matrix[3][3]};
    load_matrix(location_view_matrix, matrix);
}




}