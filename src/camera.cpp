
#include "camera.hpp"

#include "SDL.h"

namespace jac {

void camera::move()
{
    const auto state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_W]) {
        position.z -= 0.02f;
    }
    if (state[SDL_SCANCODE_S]) {
        position.z += 0.02f;
    }
    if (state[SDL_SCANCODE_D]) {
        position.x += 0.02f;
    }
    if (state[SDL_SCANCODE_A]) {
        position.x -= 0.02f;
    }
}


}
