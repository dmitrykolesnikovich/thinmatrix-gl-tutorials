
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
    load_vector(location_camera_position, camera.get_position());
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
    location_reflection_texture = get_uniform_location("reflectionTexture");
    location_refraction_texture = get_uniform_location("refractionTexture");
    location_dudv_map = get_uniform_location("dudvMap");
    location_move_factor = get_uniform_location("moveFactor");
    location_camera_position = get_uniform_location("cameraPosition");
}

void water_shader::connect_texture_units() const
{
    load_int(location_reflection_texture, 0);
    load_int(location_refraction_texture, 1);
    load_int(location_dudv_map, 2);
}

void water_shader::load_move_factor(float factor) const
{
    load_float(location_move_factor, factor);
}


}
