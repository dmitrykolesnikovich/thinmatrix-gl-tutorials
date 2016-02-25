
#include "display_manager.hpp"

#include <glad/glad.h>

namespace {

const char* get_gl_error(GLenum err)
{
    switch (err) {
    case GL_INVALID_ENUM:
        return "invalid enum";
    case GL_INVALID_VALUE:
        return "invalid value";
    case GL_INVALID_OPERATION:
        return "invalid Operation";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "invalid framebuffer operation";
    case GL_OUT_OF_MEMORY:
        return "out of memory";
    default:
        return "unknown";
    }
}

extern "C"
void error_check_callback(const char* name, void* /*funcptr*/,
                          int /*len_args*/, ...)
{
    GLenum err = GL_NO_ERROR;

    while ((err = glad_glGetError()) != GL_NO_ERROR) {
        const char* msg = get_gl_error(err);
        SDL_Log("Got GL error \"%s\" in %s", msg, name);
        SDL_assert(err != GL_NO_ERROR);
    }
}

}

namespace jac {

constexpr int width = 1280/2;
constexpr int height = 720/2;

display create_display()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                        SDL_GL_CONTEXT_DEBUG_FLAG |
                        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    auto* window = SDL_CreateWindow("Jac", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width, height,
                                    SDL_WINDOW_OPENGL |
                                    SDL_WINDOW_ALLOW_HIGHDPI);

    auto ctx = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    glad_set_post_callback(error_check_callback);

    {
        int w, h;
        SDL_GL_GetDrawableSize(window, &w, &h);
        glViewport(0, 0, w, h);
    }

    return { sdl_window_ptr(window), sdl_gl_context{ctx} };
}

void update_display(display& display)
{
    SDL_GL_SwapWindow(display.window.get());
}


}

