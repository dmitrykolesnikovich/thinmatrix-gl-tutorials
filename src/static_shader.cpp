
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
    location_shine_damper = get_uniform_location("shineDamper");
    location_reflectivity = get_uniform_location("reflectivity");
    location_use_fake_lighting = get_uniform_location("useFakeLighting");
    location_sky_colour = get_uniform_location("skyColour");
    location_number_of_rows = get_uniform_location("numberOfRows");
    location_offset = get_uniform_location("offset");
    location_plane = get_uniform_location("plane");

    for (int i = 0; i < max_lights; i++) {
        auto i_s = std::to_string(i);
        location_light_position[i] = get_uniform_location("lightPosition[" + i_s + "]");
        location_light_colour[i] = get_uniform_location("lightColour[" + i_s + "]");
        location_attenuation[i] = get_uniform_location("attenuation[" + i_s + "]");
    }
}

void static_shader::load_transformation_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_transformation_matrix, matrix);
}

void static_shader::load_lights(const std::vector<light>& lights) const
{
    for (int i = 0; i < max_lights; i++) {
        if (i < lights.size()) {
            load_vector(location_light_position[i], lights[i].position);
            load_vector(location_light_colour[i], lights[i].colour);
            load_vector(location_attenuation[i], lights[i].attenuation);
        } else {
            load_vector(location_light_position[i], glm::vec3{0, 0, 0});
            load_vector(location_light_position[i], glm::vec3{0, 0, 0});
            load_vector(location_light_position[i], glm::vec3{1, 0, 0});
        }
    }
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

void static_shader::load_number_of_rows(int num_rows) const
{
    load_float(location_number_of_rows, num_rows);
}

void static_shader::load_offset(float x_offset, float y_offset) const
{
    load_vector2d(location_offset, glm::vec2{x_offset, y_offset});
}

void static_shader::load_clip_plane(const glm::vec4& plane) const
{
    load_vector(location_plane, plane);
}


}
