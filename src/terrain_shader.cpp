
#include "terrain_shader.hpp"

#include "camera.hpp"
#include "light.hpp"
#include "maths.hpp"

constexpr char vertex_shader_source[] = "shaders/terrain_vertex_shader.vert";
constexpr char fragment_shader_source[] = "shaders/terrain_fragment_shader.frag";

namespace jac {


terrain_shader::terrain_shader()
    : shader_program{vertex_shader_source, fragment_shader_source}
{
    link();
}

void terrain_shader::bind_attributes()
{
    bind_attribute(0, "position");
    bind_attribute(1, "textureCoords");
    bind_attribute(2, "normal");
}

void terrain_shader::get_all_uniform_locations()
{
    location_transformation_matrix = get_uniform_location("transformationMatrix");
    location_projection_matrix = get_uniform_location("projectionMatrix");
    location_view_matrix = get_uniform_location("viewMatrix");
    location_shine_damper = get_uniform_location("shineDamper");
    location_reflectivity = get_uniform_location("reflectivity");
    location_sky_colour = get_uniform_location("skyColour");
    location_background_texture = get_uniform_location("backgroundTexture");
    location_r_texture = get_uniform_location("rTexture");
    location_g_texture = get_uniform_location("gTexture");
    location_b_texture = get_uniform_location("bTexture");
    location_blend_map = get_uniform_location("blendMap");

    for (int i = 0; i < max_lights; i++) {
        location_light_position[i] = get_uniform_location("lightPosition[" + std::to_string(i) + "]");
        location_light_colour[i] = get_uniform_location("lightColour[" + std::to_string(i) + "]");
    }
}

void terrain_shader::load_transformation_matrix(const glm::mat4& matrix) const
{
    load_matrix(location_transformation_matrix, matrix);
}

void terrain_shader::load_lights(const std::vector<light>& lights) const
{
    for (int i = 0; i < max_lights; i++) {
        if (i < lights.size()) {
            load_vector(location_light_position[i], lights[i].position);
            load_vector(location_light_colour[i], lights[i].colour);
        }
        else {
            load_vector(location_light_position[i], glm::vec3{0, 0, 0});
            load_vector(location_light_colour[i], glm::vec3{0, 0, 0});
        }
    }
}

void terrain_shader::load_view_matrix(const camera& camera) const
{
    load_matrix(location_view_matrix, maths::create_view_matrix(camera));
}

void terrain_shader::load_projection_matrix(const glm::mat4& projection) const
{
    load_matrix(location_projection_matrix, projection);
}

void terrain_shader::load_shine_variables(float damper, float reflectivity) const
{
    load_float(location_shine_damper, damper);
    load_float(location_reflectivity, reflectivity);
}

void terrain_shader::load_sky_colour(float r, float g, float b) const
{
    load_vector(location_sky_colour, {r, g, b});
}

void terrain_shader::connect_texture_units() const
{
    load_int(location_background_texture, 0);
    load_int(location_r_texture, 1);
    load_int(location_g_texture, 2);
    load_int(location_b_texture, 3);
    load_int(location_blend_map, 4);
}

}
