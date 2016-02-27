
#include "master_renderer.hpp"

#include "camera.hpp"
#include "entity.hpp"
#include "light.hpp"
#include "renderer.hpp"
#include "static_shader.hpp"
#include "textured_model.hpp"

#include <unordered_map>
#include <vector>

namespace jac {

struct master_renderer::pimpl {
    static_shader shader{};
    renderer renderer{shader};

    entity_map entities;
};

master_renderer::master_renderer()
    : priv{std::make_unique<pimpl>()}
{}

master_renderer::master_renderer(master_renderer&&) = default;
master_renderer& master_renderer::operator=(master_renderer&&) = default;
master_renderer::~master_renderer() = default;

void master_renderer::render(const light& sun, const camera& cam) const
{
    priv->renderer.prepare();
    priv->shader.start();
    priv->shader.load_light(sun);
    priv->shader.load_view_matrix(cam);
    priv->renderer.render(priv->entities);
    priv->shader.stop();
    priv->entities.clear();
}

void master_renderer::process_entity(const entity& entity)
{
    const auto& entity_model = entity.model;

    auto& batch = priv->entities[entity_model];
    batch.push_back(&entity);
}

}
