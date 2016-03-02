
#include "water_frame_buffers.hpp"

#include "SDL.h"

namespace jac {

water_frame_buffers::water_frame_buffers()
{
    initialise_reflection_frame_buffer();
    initialise_refraction_frame_buffer();
}

void water_frame_buffers::bind_reflection_frame_buffer() const
{
    bind_frame_buffer(reflection_framebuffer.get(), reflection_width, reflection_height);
}

void water_frame_buffers::bind_refraction_frame_buffer() const
{
    bind_frame_buffer(refraction_framebuffer.get(), refraction_width, refraction_height);
}

void water_frame_buffers::unbind_current_frame_buffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    int w, h;
    SDL_GL_GetDrawableSize(SDL_GL_GetCurrentWindow(), &w, &h);

    glViewport(0, 0, w, h);
}

void water_frame_buffers::initialise_reflection_frame_buffer()
{
    reflection_framebuffer = create_frame_buffer();
    reflection_texture = create_texture_attachment(reflection_width, reflection_height);
    reflection_depth_buffer = create_depth_buffer_attachment(reflection_width, reflection_height);
    unbind_current_frame_buffer();
}

void water_frame_buffers::initialise_refraction_frame_buffer()
{
    refraction_framebuffer = create_frame_buffer();
    refraction_texture = create_texture_attachment(refraction_width, refraction_height);
    refraction_depth_texture = create_depth_texture_attachment(refraction_width, refraction_height);
    unbind_current_frame_buffer();
}

void water_frame_buffers::bind_frame_buffer(GLuint framebuffer, int width,
                                            int height) const
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, width, height);
}

gl::framebuffer_handle water_frame_buffers::create_frame_buffer()
{
    gl::framebuffer_handle fb;
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb.get());
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    return fb;
}

gl::texture_handle water_frame_buffers::create_texture_attachment(int width,
                                                                  int height)
{
    gl::texture_handle tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex.get());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex.get(), 0);
    return tex;
}

gl::texture_handle water_frame_buffers::create_depth_texture_attachment(
        int width, int height)
{
    gl::texture_handle tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex.get());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex.get(), 0);
    return tex;
}

gl::renderbuffer_handle water_frame_buffers::create_depth_buffer_attachment(
        int width, int height)
{
    gl::renderbuffer_handle buf;
    glGenRenderbuffers(1, &buf);
    glBindRenderbuffer(GL_RENDERBUFFER, buf.get());
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buf.get());
    return buf;
}


}
