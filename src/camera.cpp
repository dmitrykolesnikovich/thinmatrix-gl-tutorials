
#include "camera.hpp"

#include "SDL.h"

constexpr float move_step = 0.04f;

namespace jac {

void camera::move()
{
    const auto state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_W]) {
        position.z -= move_step;
    }
    if (state[SDL_SCANCODE_S]) {
        position.z += move_step;
    }
    if (state[SDL_SCANCODE_D]) {
        position.x += move_step;
    }
    if (state[SDL_SCANCODE_A]) {
        position.x -= move_step;
    }
    if (state[SDL_SCANCODE_UP]) {
        position.y += move_step;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        position.y -= move_step;
    }
}


}
