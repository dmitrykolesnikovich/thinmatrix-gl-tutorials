
#ifndef JAC_SDL_HANDLES_HPP
#define JAC_SDL_HANDLES_HPP

#include "SDL.h"

#include <memory>

namespace jac {

namespace detail {

template <class T, void (*DeleteFunc)(T*)>
struct sdl_deleter {
    void operator()(T* ptr) const {
        DeleteFunc(ptr);
    }
};

}

template <class T, void(*Deleter)(T*)>
using sdl_ptr = std::unique_ptr<T, detail::sdl_deleter<T, Deleter>>;

using sdl_gl_context = sdl_ptr<void, SDL_GL_DeleteContext>;
using sdl_surface_ptr = sdl_ptr<SDL_Surface, SDL_FreeSurface>;
using sdl_window_ptr = sdl_ptr<SDL_Window, SDL_DestroyWindow>;
}

#endif
