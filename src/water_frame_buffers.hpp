
#ifndef JAC_WATER_FRAME_BUFFERS_HPP
#define JAC_WATER_FRAME_BUFFERS_HPP

#include "gl_handles.hpp"

#include <glad/glad.h>

namespace jac {

class water_frame_buffers {
public:
    water_frame_buffers();

    void bind_reflection_frame_buffer() const;

    void bind_refraction_frame_buffer() const;

    void unbind_current_frame_buffer() const;

    GLuint get_reflection_texture() const { return reflection_texture.get(); }

    GLuint get_refraction_texture() const { return refraction_texture.get(); }

    GLuint get_refraction_depth_texture() const { return refraction_depth_texture.get(); }

protected:
    static constexpr int reflection_width = 320;
    static constexpr int refraction_width = 180;

private:
    static constexpr int reflection_height = 1280;
    static constexpr int refraction_height = 720;

    void initialise_reflection_frame_buffer();
    void initialise_refraction_frame_buffer();
    void bind_frame_buffer(GLuint framebuffer, int width, int height) const;

    gl::framebuffer_handle create_frame_buffer();
    gl::texture_handle create_texture_attachment(int width, int height);
    gl::texture_handle create_depth_texture_attachment(int width, int height);
    gl::renderbuffer_handle create_depth_buffer_attachment(int width, int height);

    gl::framebuffer_handle reflection_framebuffer;
    gl::texture_handle reflection_texture;
    gl::renderbuffer_handle reflection_depth_buffer;

    gl::framebuffer_handle refraction_framebuffer;
    gl::texture_handle refraction_texture;
    gl::texture_handle refraction_depth_texture;

};

}

#endif //JAC_WATER_FRAME_BUFFERS_HPP
