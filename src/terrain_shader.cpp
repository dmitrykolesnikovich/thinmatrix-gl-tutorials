
#include "terrain_shader.hpp"

#include "maths.hpp"

constexpr char vertex_shader_source[] = "shaders/terrain_vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/terrain_fragment_shader.frag";

namespace jac {

struct terrain_shader::pimpl {
    int location_transformation_matrix = 0;
    int location_projection_matrix = 0;
    int location_view_matrix = 0;
    int location_light_position = 0;
    int location_light_colour = 0;
    int location_shine_damper = 0;
    int location_reflectivity = 0;
    int location_sky_colour = 0;
};

terrain_shader::terrain_shader()
    : shader_program{vertex_shader_source, fragment_shader_source},
      priv{std::make_unique<pimpl>()}
{
    link();
}

terrain_shader::terrain_shader(terrain_shader&&) = default;
terrain_shader& terrain_shader::operator=(terrain_shader&&) = default;
terrain_shader::~terrain_shader() = default;

void terrain_shader::bind_attributes()
{
    bind_attribute(0, "position");
    bind_attribute(1, "textureCoords");
    bind_attribute(2, "normal");
}

void terrain_shader::get_all_uniform_locations()
{
    priv->location_transformation_matrix = get_uniform_location("transformationMatrix");
    priv->location_projection_matrix = get_uniform_location("projectionMatrix");
    priv->location_view_matrix = get_uniform_location("viewMatrix");
    priv->location_light_position = get_uniform_location("lightPosition");
    priv->location_light_colour = get_uniform_location("lightColour");
    priv->location_shine_damper = get_uniform_location("shineDamper");
    priv->location_reflectivity = get_uniform_location("reflectivity");
    priv->location_sky_colour = get_uniform_location("skyColour");
}

void terrain_shader::load_transformation_matrix(const glm::mat4& matrix) const
{
    load_matrix(priv->location_transformation_matrix, matrix);
}

void terrain_shader::load_light(const light& light) const
{
    load_vector(priv->location_light_position, light.position);
    load_vector(priv->location_light_colour, light.colour);
}

void terrain_shader::load_view_matrix(const camera& camera) const
{
    load_matrix(priv->location_view_matrix, maths::create_view_matrix(camera));
}

void terrain_shader::load_projection_matrix(const glm::mat4& projection) const
{
    load_matrix(priv->location_projection_matrix, projection);
}

void terrain_shader::load_shine_variables(float damper, float reflectivity) const
{
    load_float(priv->location_shine_damper, damper);
    load_float(priv->location_reflectivity, reflectivity);
}

void terrain_shader::load_sky_colour(float r, float g, float b) const
{
    load_vector(priv->location_sky_colour, {r, g, b});
}

}
