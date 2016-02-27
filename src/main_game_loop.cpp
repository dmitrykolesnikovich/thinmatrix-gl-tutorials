
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

    auto tree = jac::textured_model{jac::load_obj_model("tree", loader),
            jac::model_texture{loader.load_texture("tree")}};

    auto grass = jac::textured_model{jac::load_obj_model("grassModel", loader),
            jac::model_texture{loader.load_texture("grassTexture")}};
    grass.texture.has_transparency = true;
    grass.texture.use_fake_lighting = true;

    auto flower = jac::textured_model{grass.raw,
            jac::model_texture{loader.load_texture("flower")}};
    flower.texture.has_transparency = true;
    flower.texture.use_fake_lighting = true;

    auto fern = jac::textured_model{jac::load_obj_model("fern", loader),
            jac::model_texture{loader.load_texture("fern")}};
    fern.texture.has_transparency = true;

    auto tree2 = jac::textured_model{jac::load_obj_model("lowPolyTree", loader),
            jac::model_texture{loader.load_texture("lowPolyTree")}};

    auto light = jac::light{{3000, 2000, 2000}, {1.0f, 1.0f, 1.0f}};

    auto terrain = jac::terrain{0, -1, loader, jac::model_texture{loader.load_texture("grass")}};
    auto terrain2 = jac::terrain{-1, -1, loader, jac::model_texture{loader.load_texture("grass")}};

    std::vector<jac::entity> entities;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dist{-400, 400};

    for (int i = 0; i < 500; i++) {
        entities.push_back(jac::entity{tree, {dist(gen), 0, dist(gen)}, 0, 0, 0, 3});
        entities.push_back(jac::entity{grass, {dist(gen), 0, dist(gen)}, 0, 0, 0, 1});
        entities.push_back(jac::entity{flower, {dist(gen), 0, dist(gen)}, 0, 0, 0, 1});
        entities.push_back(jac::entity{fern, {dist(gen), 0, dist(gen)}, 0, 0, 0, 0.6f});
        entities.push_back(jac::entity{tree2, {dist(gen), 0, dist(gen)}, 0, 0, 0, 0.4f});
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

        camera.move();
        renderer.process_terrain(terrain);
        renderer.process_terrain(terrain2);

        for (const auto& e : entities) {
            renderer.process_entity(e);
        }
        renderer.render(light, camera);

        jac::update_display(display);
    }

    SDL_Quit();
}
