
#ifndef JAC_WATER_SHADER_HPP
#define JAC_WATER_SHADER_HPP

#include "shader_program.hpp"
#include "camera.hpp"

namespace jac {

class water_shader final : public shader_program {
public:
    water_shader();

    void load_projection_matrix(const glm::mat4& matrix) const;
    void load_view_matrix(const jac::camera& camera) const;
    void load_model_matrix(const glm::mat4& matrix) const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    unsigned location_model_matrix = 0;
    unsigned location_view_matrix = 0;
    unsigned location_projection_matrix = 0;
};

}

#endif //JAC_WATER_SHADER_HPP
