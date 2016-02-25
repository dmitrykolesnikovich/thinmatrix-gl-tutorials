
#include "display_manager.hpp"

#include "SDL.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    auto display = jac::create_display();

    bool quit_requested = false;
    while (!quit_requested) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit_requested = true;
                break;
            }
        }

        // game logic
        // render
        jac::update_display(display);
    }

    SDL_Quit();
}
