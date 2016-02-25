#ifndef JAC_STATIC_SHADER_HPP
#define JAC_STATIC_SHADER_HPP

#include "shader_program.hpp"

namespace jac {

class static_shader : public shader_program
{
public:
    static_shader();

private:
    virtual void bind_attributes() override;
};


}

#endif
