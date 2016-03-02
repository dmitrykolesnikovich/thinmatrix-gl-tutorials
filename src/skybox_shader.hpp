
#ifndef JAC_SKYBOX_SHADER_HPP
#define JAC_SKYBOX_SHADER_HPP

#include "shader_program.hpp"

namespace jac {

class camera;

class skybox_shader final : public shader_program
{
public:
    skybox_shader();

    void load_projection_matrix(const glm::mat4& matrix) const;

    void load_view_matrix(const camera& matrix);

    void load_fog_colour(float r, float g, float b) const;

    void load_blend_factor(float factor) const;

    void connect_texture_units() const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    float rotation = 0.0f;

    int location_projection_matrix = 0;
    int location_view_matrix = 0;
    int location_fog_colour = 0;
    int location_cube_map = 0;
    int location_cube_map2 = 0;
    int location_blend_factor = 0;
};


}

#endif
