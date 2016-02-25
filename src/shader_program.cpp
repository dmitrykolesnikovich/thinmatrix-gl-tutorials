
#include "shader_program.hpp"

#include "gl_handles.hpp"

#include "SDL.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace jac {

struct shader_program::pimpl {
    gl::program_handle program;
    gl::shader_handle vertex_shader;
    gl::shader_handle fragment_shader;

    gl::shader_handle load_shader(const std::string& filename, GLenum type) {
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
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", log.c_str());
        }

        return shader;
    }
};

shader_program::shader_program(const std::string& vertex_shader,
                               const std::string& fragment_shader)
    : priv(std::make_unique<pimpl>())
{
    priv->vertex_shader = priv->load_shader(vertex_shader, GL_VERTEX_SHADER);
    priv->fragment_shader = priv->load_shader(fragment_shader, GL_FRAGMENT_SHADER);
    priv->program = glCreateProgram();

    glAttachShader(priv->program.get(), priv->vertex_shader.get());
    glAttachShader(priv->program.get(), priv->fragment_shader.get());
}

shader_program::~shader_program()
{
    stop();
    glDetachShader(priv->program.get(), priv->vertex_shader.get());
    glDetachShader(priv->program.get(), priv->fragment_shader.get());
}

void shader_program::link()
{
    bind_attributes();
    glLinkProgram(priv->program.get());
    glValidateProgram(priv->program.get());
}

void shader_program::start()
{
    glUseProgram(priv->program.get());
}

void shader_program::stop()
{
    glUseProgram(0);
}

void shader_program::bind_attribute(GLuint attribute,
                                    const std::string& variable_name)
{
    glBindAttribLocation(priv->program.get(), attribute, variable_name.c_str());
}

}