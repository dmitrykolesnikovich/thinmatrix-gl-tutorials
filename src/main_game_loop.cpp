
#include "display_manager.hpp"
#include "entity.hpp"
#include "loader.hpp"
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
    auto shader = jac::static_shader{};
    auto renderer = jac::renderer{shader};

    auto model = jac::load_obj_model("stall", loader);
    auto texture = jac::model_texture{loader.load_texture("stallTexture")};
    auto static_model = jac::textured_model{model, texture};

    auto entity = jac::entity{static_model, glm::vec3{0, 0, -50}, 0, 0, 0, 1};
    auto camera = jac::camera{};


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

        entity.increase_rotation(0, 1, 0);
        camera.move();
        renderer.prepare();
        shader.start();
        shader.load_view_matrix(camera);
        renderer.render(entity, shader);
        shader.stop();
        jac::update_display(display);
    }

    SDL_Quit();
}
