
#ifndef JAC_WATER_SHADER_HPP
#define JAC_WATER_SHADER_HPP

#include "shader_program.hpp"

namespace jac {

class camera;
struct light;

class water_shader final : public shader_program {
public:
    water_shader();

    void load_projection_matrix(const glm::mat4& matrix) const;
    void load_view_matrix(const jac::camera& camera) const;
    void load_model_matrix(const glm::mat4& matrix) const;
    void load_move_factor(float factor) const;
    void load_light(const jac::light& light) const;
    void connect_texture_units() const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    int location_model_matrix = 0;
    int location_view_matrix = 0;
    int location_projection_matrix = 0;
    int location_reflection_texture = 0;
    int location_refraction_texture = 0;
    int location_dudv_map = 0;
    int location_move_factor = 0;
    int location_camera_position = 0;
    int location_normal_map = 0;
    int location_light_colour = 0;
    int location_light_position = 0;
    int location_depth_map = 0;
};

}

#endif //JAC_WATER_SHADER_HPP
