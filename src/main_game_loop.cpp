
#include "display_manager.hpp"
#include "entity.hpp"
#include "light.hpp"
#include "loader.hpp"
#include "master_renderer.hpp"
#include "model_texture.hpp"
#include "obj_loader.hpp"
#include "static_shader.hpp"
#include "terrain.hpp"
#include "textured_model.hpp"

#include "SDL.h"

#include <random>
#include <vector>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    auto display = jac::create_display();
    auto loader = jac::loader{};

    auto model = jac::load_obj_model("tree", loader);
    auto texture = jac::model_texture{loader.load_texture("tree")};
    auto static_model = jac::textured_model{model, texture};

    auto entity = jac::entity{static_model, {0, 0, -25}, 0, 0, 0, 1};
    auto light = jac::light{{3000, 2000, 2000}, {1.0f, 1.0f, 1.0f}};

    auto terrain = jac::terrain{0, -1, loader, jac::model_texture{loader.load_texture("grass")}};
    auto terrain2 = jac::terrain{-1, -1, loader, jac::model_texture{loader.load_texture("grass")}};

    std::vector<jac::entity> trees;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist{-100, 100};

    for (int i = 0; i < 200; i++) {
        trees.push_back(jac::entity{static_model, {dist(gen), 0, dist(gen)}, 0, 0, 0, 1});
    }

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
        renderer.process_terrain(terrain);
        renderer.process_terrain(terrain2);

        for (const auto& e : trees) {
            renderer.process_entity(e);
        }
        renderer.process_entity(entity);
        renderer.render(light, camera);

        jac::update_display(display);
    }

    SDL_Quit();
}
