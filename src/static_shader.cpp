
#include "static_shader.hpp"

#include "light.hpp"
#include "maths.hpp"

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
    bind_attribute(1, "textureCoords");
    bind_attribute(2, "normal");
}

void static_shader::get_all_uniform_locations()
{
    location_transformation_matrix = get_uniform_location("transformationMatrix");
    location_projection_matrix = get_uniform_location("projectionMatrix");
    location_view_matrix = get_uniform_location("viewMatrix");
    location_light_position = get_uniform_location("lightPosition");
    location_light_colour = get_uniform_location("lightColour");
    location_shine_damper = get_uniform_location("shineDamper");
    location_reflectivity = get_uniform_location("reflectivity");
    location_use_fake_lighting = get_uniform_location("useFakeLighting");
    location_sky_colour = get_uniform_location("skyColour");
}

void static_shader::load_transformation_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_transformation_matrix, matrix);
}

void static_shader::load_light(const light& light) const
{
    load_vector(location_light_position, light.position);
    load_vector(location_light_colour, light.colour);
}

void static_shader::load_view_matrix(const camera& camera) const
{
    load_matrix(location_view_matrix, maths::create_view_matrix(camera));
}

void static_shader::load_projection_matrix(const glm::mat4& projection) const
{
    load_matrix(location_projection_matrix, projection);
}

void static_shader::load_shine_variables(float damper, float reflectivity) const
{
    load_float(location_shine_damper, damper);
    load_float(location_reflectivity, reflectivity);
}

void static_shader::load_fake_lighting_variable(bool use_fake) const
{
    load_bool(location_use_fake_lighting, use_fake);
}

void static_shader::load_sky_colour(float r, float g, float b) const
{
    load_vector(location_sky_colour, {r, g, b});
}

}
