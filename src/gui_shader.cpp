
#include "gui_shader.hpp"

constexpr const char vertex_file[] = "shaders/gui_vertex_shader.vert";
constexpr const char fragment_file[] = "shaders/gui_fragment_shader.frag";

namespace jac {

gui_shader::gui_shader()
    : shader_program(vertex_file, fragment_file)
{
    link();
}

void gui_shader::load_transformation(const glm::mat4& matrix) const
{
    load_matrix(location_transformation_matrix, matrix);
}

void gui_shader::bind_attributes()
{
    bind_attribute(0, "position");
}

void gui_shader::get_all_uniform_locations()
{
    location_transformation_matrix = get_uniform_location("transformationMatrix");
}


}
