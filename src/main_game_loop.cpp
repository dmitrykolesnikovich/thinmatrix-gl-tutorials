
#include "camera.hpp"
#include "display_manager.hpp"
#include "entity.hpp"
#include "light.hpp"
#include "loader.hpp"
#include "master_renderer.hpp"
#include "obj_loader.hpp"
#include "player.hpp"
#include "terrain.hpp"

#include "SDL.h"

#include <random>
#include <vector>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    auto display = jac::create_display();
    auto loader = jac::loader{};

    // Terrain texure stuff
    auto background_texture = jac::terrain_texture{loader.load_texture("grassy")};
    auto r_texture = jac::terrain_texture{loader.load_texture("dirt")};
    auto g_texture = jac::terrain_texture{loader.load_texture("pinkFlowers")};
    auto b_texture = jac::terrain_texture{loader.load_texture("path")};
    auto texture_pack = jac::terrain_texture_pack{background_texture, r_texture,
            g_texture, b_texture};
    auto blend_map = jac::terrain_texture{loader.load_texture("blendMap")};


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

    auto bobble = jac::textured_model{jac::load_obj_model("lowPolyTree", loader),
            jac::model_texture{loader.load_texture("lowPolyTree")}};

    auto light = jac::light{{20'000, 40'000, 20'000}, {1.0f, 1.0f, 1.0f}};

    auto terrain = jac::terrain{0, -1, loader, texture_pack, blend_map, "heightmap"};

    std::vector<jac::entity> entities;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<float> dist{0, 1.0f};

    auto rand_vec = [&] {
        float x = dist(gen) * 800 - 400;
        float z = dist(gen) * -600;
        return glm::vec3{x, terrain.get_height_of_terrain(x, z), z};
    };

    for (int i = 0; i < 400; i++) {
        if (i % 7 == 0) {
            entities.push_back(jac::entity{grass,
                                           rand_vec(),
                                           0, 0, 0, 1.8f});
            entities.push_back(jac::entity{flower,
                                           rand_vec(),
                                           0, 0, 0, 2.3f});
        }
        if (i % 3 == 0) {
            entities.push_back(jac::entity{fern,
                                           rand_vec(),
                                           0, dist(gen) * 360, 0, 0.9f});
            entities.push_back(jac::entity{bobble,
                                           rand_vec(),
                                           0, dist(gen) * 360, 0, dist(gen) * 0.1f + 0.6f});
            entities.push_back(jac::entity{tree,
                                           rand_vec(),
                                           0, dist(gen) * 360, 0, dist(gen) * 1.0f + 4.0f});
        }
    }

    auto dragon = jac::textured_model{jac::load_obj_model("dragon", loader),
                jac::model_texture{loader.load_texture("grass")}};
    entities.push_back(jac::entity{dragon, {100, 0, -50}, 0, 0, 0, 3.0});

    auto person = jac::textured_model{jac::load_obj_model("person", loader),
                jac::model_texture{loader.load_texture("playerTexture")}};

    auto player = jac::player(person, {100, 0, -50}, 0, 0, 0, 1.0);
    auto camera = jac::camera{player};

    auto renderer = jac::master_renderer{};

    bool quit_requested = false;
    while (!quit_requested) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit_requested = true;
                break;
            case SDL_MOUSEMOTION:
                camera.mouse_move(e.motion.xrel, e.motion.yrel);
                break;
            case SDL_MOUSEWHEEL:
                camera.mouse_wheel(e.wheel.y);
                break;
            }
        }

        camera.move();
        player.move(terrain);
        renderer.process_terrain(terrain);

        for (const auto& e : entities) {
            renderer.process_entity(e);
        }

        renderer.process_entity(player);
        renderer.render(light, camera);

        jac::update_display(display);
    }

    SDL_Quit();
}
