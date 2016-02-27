#ifndef JAC_MASTER_RENDERER_HPP
#define JAC_MASTER_RENDERER_HPP

#include "entity_renderer.hpp"
#include "static_shader.hpp"
#include "terrain_renderer.hpp"
#include "terrain_shader.hpp"


#include <glm/mat4x4.hpp>

#include <unordered_map>
#include <vector>

namespace jac {

struct camera;
struct entity;
struct light;
struct terrain;
struct textured_model;

class master_renderer
{
public:
    master_renderer();

    void prepare() const;

    void render(const light& sun, const camera& cam);

    void process_entity(const entity& entity);
    void process_terrain(const terrain& terrain);

    static void enable_culling();
    static void disable_culling();

private:
    using terrain_list = std::vector<const terrain*>;
    using entity_map = std::unordered_map<textured_model, std::vector<const entity*>>;

    static glm::mat4 create_projection_matrix();

    static_shader shader{};
    glm::mat4 projection_matrix{create_projection_matrix()};
    entity_renderer entity_renderer{shader, projection_matrix};
    terrain_shader terrain_shader{};
    terrain_renderer terrain_renderer{terrain_shader, projection_matrix};

    entity_map entities;
    terrain_list terrains;
};


}

#endif
