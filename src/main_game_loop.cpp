
#include "display_manager.hpp"
#include "entity.hpp"
#include "light.hpp"
#include "loader.hpp"
#include "master_renderer.hpp"
#include "model_texture.hpp"
#include "obj_loader.hpp"
#include "renderer.hpp"
#include "static_shader.hpp"
#include "textured_model.hpp"

#include "SDL.h"

#include <vector>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    auto display = jac::create_display();
    auto loader = jac::loader{};

    auto model = jac::load_obj_model("dragon", loader);
    auto texture = jac::model_texture{loader.load_texture("white")};
    texture.shine_damper = 10;
    texture.reflectivity = 1;
    auto static_model = jac::textured_model{model, texture};

    auto entity = jac::entity{static_model, {0, -2, -25}, 0, 0, 0, 1};
    auto light = jac::light{{0.0f, 10.0f, -20.0f}, {1.0f, 1.0f, 1.0f}};

    auto camera = jac::camera{};

    auto renderer = jac::master_renderer{};



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

        entity.increase_rotation(0, 2, 0);
        camera.move();
        renderer.process_entity(entity);
        renderer.render(light, camera);

        jac::update_display(display);
    }

    SDL_Quit();
}
