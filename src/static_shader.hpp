#ifndef JAC_STATIC_SHADER_HPP
#define JAC_STATIC_SHADER_HPP

#include "shader_program.hpp"

#include <glm/mat4x4.hpp>

namespace jac {

class static_shader : public shader_program
{
public:
    static_shader();

    void load_transformation_matrix(const glm::mat4& matrix);

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    int location_transformation_matrix = 0;
};


}

#endif
