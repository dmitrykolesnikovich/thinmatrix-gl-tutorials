
#ifndef JAC_SHADER_PROGRAM_HPP
#define JAC_SHADER_PROGRAM_HPP

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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

    void start() const;
    void stop() const;

protected:
    void link();
    virtual void bind_attributes() = 0;
    virtual void get_all_uniform_locations() = 0;
    void bind_attribute(GLuint attribute, const std::string& variable_name);
    GLint get_uniform_location(const std::string& uniform_name) const;
    void load_float(GLint location, float value) const;
    void load_vector(GLint location, const glm::vec3& vector) const;
    void load_bool(GLint location, bool value) const;
    void load_matrix(GLint location, const glm::mat4& matrix) const;
    void load_int(GLint location, int value) const;

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};

}

#endif
