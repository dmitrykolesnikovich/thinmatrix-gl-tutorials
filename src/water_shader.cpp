
#include "water_shader.hpp"

#include "camera.hpp"
#include "maths.hpp"

constexpr char vertex_shader_source[] = "shaders/water_vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/water_fragment_shader.frag";


namespace jac {

water_shader::water_shader()
    : shader_program(vertex_shader_source, fragment_shader_source)
{
    link();
}

void water_shader::load_projection_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_projection_matrix, matrix);
}

void water_shader::load_view_matrix(const jac::camera& camera) const
{
    auto matrix = maths::create_view_matrix(camera);
    load_matrix(location_view_matrix, matrix);
}

void water_shader::load_model_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_model_matrix, matrix);
}

void water_shader::bind_attributes()
{
    bind_attribute(0, "position");
}

void water_shader::get_all_uniform_locations()
{
    location_projection_matrix = get_uniform_location("projectionMatrix");
    location_view_matrix = get_uniform_location("viewMatrix");
    location_model_matrix = get_uniform_location("modelMatrix");
}

}
