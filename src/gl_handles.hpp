
#ifndef JAC_GL_HANDLES_HPP
#define JAC_GL_HANDLES_HPP

#include <glad/glad.h>
#include <algorithm>
#include <array>

namespace jac {
namespace gl {

namespace detail {

template <class Deleter>
class handle {
public:
    handle() = default;
    handle(GLuint id) : id(id) {}

    handle(handle&& other)
        : id(other.id)
    {
        other.id = 0;
    }

    handle& operator=(handle&& other)
    {
        std::swap(id, other.id);
        return *this;
    }

    ~handle()
    {
        if (id) {
            Deleter{}(id);
        }
    }

    GLuint get() const { return id; }

private:
    GLuint id = 0;
};

template <class Deleter, std::size_t N = 1>
class multi_handle {
public:
    multi_handle() = default;

    multi_handle(multi_handle&& other)
        : ids(std::move(other.ids))
    {
        std::fill(std::begin(other.ids), std::end(other.ids), 0);
    }

    multi_handle& operator=(multi_handle&& other)
    {
        std::swap(ids, other.ids);
        return *this;
    }

    ~multi_handle() { Deleter()(N, ids.data()); }

    GLuint* operator&()
    {
        return ids.data();
    }

    GLuint get(std::size_t n = 0) const {
        return ids[n];
    }

private:
    std::array<GLuint, N> ids = {};
};

struct gl_buffer_deleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteBuffers(count, ptr);
    }
};

struct gl_framebuffer_deleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteFramebuffers(count, ptr);
    }
};

struct gl_program_deleter {
    void operator()(GLuint handle) const {
        glDeleteProgram(handle);
    }
};

struct gl_shader_deleter {
    void operator()(GLuint handle) const {
        glDeleteShader(handle);
    }
};

struct gl_texture_deleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteTextures(count, ptr);
    }
};

struct gl_vertex_array_deleter {
    void operator()(GLsizei count, GLuint* ptr) const {
        glDeleteVertexArrays(count, ptr);
    }
};

} // end namespace detail

using buffer_handle = detail::multi_handle<detail::gl_buffer_deleter>;
using framebuffer_handle = detail::multi_handle<detail::gl_framebuffer_deleter>;
using program_handle = detail::handle<detail::gl_program_deleter>;
using shader_handle = detail::handle<detail::gl_shader_deleter>;
using texture_handle = detail::multi_handle<detail::gl_texture_deleter>;
using vertex_array_handle = detail::multi_handle<detail::gl_vertex_array_deleter>;

} // end namespace gl
} // end namespace jac

#endif
