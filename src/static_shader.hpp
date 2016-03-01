#ifndef JAC_STATIC_SHADER_HPP
#define JAC_STATIC_SHADER_HPP

#include "shader_program.hpp"

#include <glm/mat4x4.hpp>
#include <vector>

namespace jac {

class camera;
struct light;

class static_shader final : public shader_program
{
public:
    static_shader();

    void load_transformation_matrix(const glm::mat4& matrix) const;
    void load_projection_matrix(const glm::mat4& projection) const;
    void load_view_matrix(const camera& camera) const;
    void load_lights(const std::vector<light>& lights) const;
    void load_shine_variables(float damper, float reflectivity) const;
    void load_fake_lighting_variable(bool use_fake) const;
    void load_sky_colour(float r, float g, float b) const;
    void load_number_of_rows(int num_rows) const;
    void load_offset(float x_offset, float y_offset) const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    static constexpr int max_lights = 4;

    int location_transformation_matrix = 0;
    int location_projection_matrix = 0;
    int location_view_matrix = 0;
    int location_light_position[max_lights] = { 0, };
    int location_light_colour[max_lights] = { 0, };
    int location_attenuation[max_lights] = { 0, };
    int location_shine_damper = 0;
    int location_reflectivity = 0;
    int location_use_fake_lighting = 0;
    int location_sky_colour = 0;
    int location_number_of_rows = 0;
    int location_offset = 0;
};


}

#endif
