
#include "static_shader.hpp"

#include "maths.hpp"

constexpr char vertex_shader_source[] = "shaders/vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/fragment_shader.frag";

namespace jac {

struct static_shader::pimpl {
    int location_transformation_matrix = 0;
    int location_projection_matrix = 0;
    int location_view_matrix = 0;
};

static_shader::static_shader()
    : shader_program{vertex_shader_source, fragment_shader_source},
      priv{std::make_unique<pimpl>()}
{
    link();
}

static_shader::static_shader(static_shader&&) = default;
static_shader& static_shader::operator=(static_shader&&) = default;
static_shader::~static_shader() = default;

void static_shader::bind_attributes()
{
    bind_attribute(0, "position");
    bind_attribute(1, "textureCoords");
}

void static_shader::get_all_uniform_locations()
{
    priv->location_transformation_matrix = get_uniform_location("transformationMatrix");
    priv->location_projection_matrix = get_uniform_location("projectionMatrix");
    priv->location_view_matrix = get_uniform_location("viewMatrix");
}

void static_shader::load_transformation_matrix(const glm::mat4& matrix) const
{
    load_matrix(priv->location_transformation_matrix, matrix);
}

void static_shader::load_view_matrix(const camera& camera) const
{
    load_matrix(priv->location_view_matrix, create_view_matrix(camera));
}

void static_shader::load_projection_matrix(const glm::mat4& projection) const
{
    load_matrix(priv->location_projection_matrix, projection);
}

}
