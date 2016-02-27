
#include "master_renderer.hpp"

#include "camera.hpp"
#include "entity.hpp"
#include "light.hpp"
#include "entity_renderer.hpp"
#include "static_shader.hpp"
#include "terrain_renderer.hpp"
#include "terrain_shader.hpp"
#include "textured_model.hpp"

#include "SDL.h"

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <vector>

namespace {

constexpr float fov = 70; // degrees
constexpr float near_plane = 0.1f;
constexpr float far_plane = 1000.0f;
constexpr float sky_red = 0.53f;
constexpr float sky_green = 0.81f;
constexpr float sky_blue = 0.92f;

glm::mat4 create_projection_matrix()
{
    int w, h;
    SDL_GL_GetDrawableSize(SDL_GL_GetCurrentWindow(), &w, &h);
    // This is certainly easier than the Java version...
    return glm::perspectiveFov(glm::radians(fov), float(w), float(h),
                               near_plane, far_plane);
}

}


namespace jac {

struct master_renderer::pimpl {
    static_shader shader{};
    glm::mat4 projection_matrix{create_projection_matrix()};
    entity_renderer entity_renderer{shader, projection_matrix};
    terrain_shader terrain_shader{};
    terrain_renderer terrain_renderer{terrain_shader, projection_matrix};

    entity_map entities;
    terrain_list terrains;
};

master_renderer::master_renderer()
    : priv{std::make_unique<pimpl>()}
{
    enable_culling();
}

master_renderer::master_renderer(master_renderer&&) = default;
master_renderer& master_renderer::operator=(master_renderer&&) = default;
master_renderer::~master_renderer() = default;

void master_renderer::prepare() const
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(sky_red, sky_green, sky_blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void master_renderer::render(const light& sun, const camera& cam) const
{
    prepare();
    priv->shader.start();
    priv->shader.load_sky_colour(sky_red, sky_green, sky_blue);
    priv->shader.load_light(sun);
    priv->shader.load_view_matrix(cam);
    priv->entity_renderer.render(priv->entities);
    priv->shader.stop();

    priv->terrain_shader.start();
    priv->terrain_shader.load_sky_colour(sky_red, sky_green, sky_blue);
    priv->terrain_shader.load_light(sun);
    priv->terrain_shader.load_view_matrix(cam);
    priv->terrain_renderer.render(priv->terrains);
    priv->terrain_shader.stop();

    priv->terrains.clear();
    priv->entities.clear();
}

void master_renderer::process_terrain(const terrain& terrain)
{
    priv->terrains.push_back(&terrain);
}

void master_renderer::process_entity(const entity& entity)
{
    const auto& entity_model = entity.model;

    auto& batch = priv->entities[entity_model];
    batch.push_back(&entity);
}

void master_renderer::enable_culling()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void master_renderer::disable_culling()
{
    glDisable(GL_CULL_FACE);
}

}
