
#include "display_manager.hpp"
#include "loader.hpp"
#include "renderer.hpp"
#include "static_shader.hpp"

#include "SDL.h"

#include <vector>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    auto display = jac::create_display();
    auto loader = jac::loader{};
    auto renderer = jac::renderer{};

    auto shader = jac::static_shader{};

    std::vector<float> vertices = {
      -0.5f, 0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f
    };

    std::vector<int> indices = {
      0,1,3,
      3,1,2
    };

    auto model = loader.load_to_vao(vertices, indices);

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
        renderer.prepare();
        shader.start();
        renderer.render(model);
        shader.stop();
        jac::update_display(display);
    }

    SDL_Quit();
}
