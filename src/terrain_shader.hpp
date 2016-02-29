#ifndef JAC_TERRAIN_SHADER_HPP
#define JAC_TERRAIN_SHADER_HPP

#include "shader_program.hpp"

#include <glm/mat4x4.hpp>

namespace jac {

class camera;
struct light;

class terrain_shader final : public shader_program
{
public:
    terrain_shader();

    void load_transformation_matrix(const glm::mat4& matrix) const;
    void load_projection_matrix(const glm::mat4& projection) const;
    void load_view_matrix(const camera& camera) const;
    void load_light(const light& light) const;
    void load_shine_variables(float damper, float reflectivity) const;
    void load_sky_colour(float r, float g, float b) const;
    void connect_texture_units() const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    int location_transformation_matrix = 0;
    int location_projection_matrix = 0;
    int location_view_matrix = 0;
    int location_light_position = 0;
    int location_light_colour = 0;
    int location_shine_damper = 0;
    int location_reflectivity = 0;
    int location_sky_colour = 0;
    int location_background_texture = 0;
    int location_r_texture = 0;
    int location_g_texture = 0;
    int location_b_texture = 0;
    int location_blend_map = 0;
};


}

#endif
