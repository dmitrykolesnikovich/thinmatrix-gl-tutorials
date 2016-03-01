
#include "shader_program.hpp"

#include "gl_handles.hpp"

#include "SDL.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace jac {

gl::shader_handle shader_program::load_shader(const std::string& filename, GLenum type) {
    std::fstream file{filename};
    std::string data;
    std::copy(std::istreambuf_iterator<char>{file},
              std::istreambuf_iterator<char>{},
              std::back_inserter(data));

    gl::shader_handle shader = glCreateShader(type);
    const char *tmp = data.data();
    glShaderSource(shader.get(), 1, &tmp, nullptr);
    glCompileShader(shader.get());
    GLint status = GL_FALSE;
    glGetShaderiv(shader.get(), GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string log;
        GLint len;
        glGetShaderiv(shader.get(), GL_INFO_LOG_LENGTH, &len);
        log.resize(len, ' ');
        glGetShaderInfoLog(shader.get(), len, nullptr, &log[0]);
        throw std::runtime_error(log);
    }

    return shader;
}

shader_program::shader_program(const std::string& vertex_shader_file,
                               const std::string& fragment_shader_file)
    : program(glad_glCreateProgram()),
      vertex_shader{load_shader(vertex_shader_file, GL_VERTEX_SHADER)},
      fragment_shader{load_shader(fragment_shader_file, GL_FRAGMENT_SHADER)}
{
    glAttachShader(program.get(), vertex_shader.get());
    glAttachShader(program.get(), fragment_shader.get());
}

shader_program::~shader_program()
{
    stop();
    glDetachShader(program.get(), vertex_shader.get());
    glDetachShader(program.get(), fragment_shader.get());
}

void shader_program::link()
{
    bind_attributes();
    glLinkProgram(program.get());
    glValidateProgram(program.get());
    get_all_uniform_locations();
}

void shader_program::start() const
{
    glUseProgram(program.get());
}

void shader_program::stop() const
{
    glUseProgram(0);
}

void shader_program::bind_attribute(GLuint attribute,
                                    const std::string& variable_name)
{
    glBindAttribLocation(program.get(), attribute, variable_name.c_str());
}

GLint shader_program::get_uniform_location(const std::string& uniform_name) const
{
    return glGetUniformLocation(program.get(), uniform_name.c_str());
}

void shader_program::load_float(GLint location, float value) const
{
    glUniform1f(location, value);
}

void shader_program::load_vector(int location, const glm::vec3& vec) const
{
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void shader_program::load_bool(int location, bool value) const
{
    float v = value ? 1.0f : 0.0f;
    glUniform1f(location, v);
}

void shader_program::load_matrix(int location, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void shader_program::load_int(int location, int value) const
{
    glUniform1i(location, value);
}

void shader_program::load_vector2d(GLint location,
                                   const glm::vec2& vector) const
{
    glUniform2fv(location, 1, glm::value_ptr(vector));
}


}
