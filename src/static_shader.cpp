
#include "static_shader.hpp"

constexpr char vertex_shader_source[] = "shaders/vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/fragment_shader.frag";

namespace jac {

static_shader::static_shader()
    : shader_program{vertex_shader_source, fragment_shader_source}
{
    link();
}

void static_shader::bind_attributes()
{
    bind_attribute(0, "position");
    bind_attribute(1, "texture_coords");
}

void static_shader::get_all_uniform_locations()
{
    location_transformation_matrix = get_uniform_location("transformation_matrix");
}

void static_shader::load_transformation_matrix(const glm::mat4& matrix)
{
    load_matrix(location_transformation_matrix, matrix);
}


}
