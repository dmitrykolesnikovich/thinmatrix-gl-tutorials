
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

    void load_view_matrix(const camera& matrix) const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    int location_projection_matrix = 0;
    int location_view_matrix = 0;
};


}

#endif
