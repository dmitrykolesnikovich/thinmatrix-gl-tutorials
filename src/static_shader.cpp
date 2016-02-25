
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
}


}
