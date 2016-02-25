
#ifndef JAC_SHADER_PROGRAM_HPP
#define JAC_SHADER_PROGRAM_HPP

#include <glad/glad.h>

#include <memory>
#include <string>

namespace jac {

class shader_program {
public:
    shader_program(const std::string& vertex_shader,
                   const std::string& fragment_shader);

    shader_program(shader_program&&);
    shader_program& operator=(shader_program&&);
    virtual ~shader_program();

    void start();
    void stop();

protected:
    void link();
    virtual void bind_attributes() = 0;
    void bind_attribute(GLuint attribute, const std::string& variable_name);

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};

}

#endif
