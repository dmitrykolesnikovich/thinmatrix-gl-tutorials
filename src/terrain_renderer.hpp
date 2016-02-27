#ifndef JAC_TERRAIN_RENDERER_HPP
#define JAC_TERRAIN_RENDERER_HPP

#include "master_renderer.hpp"
#include "terrain_shader.hpp"

#include <glm/mat4x4.hpp>

#include <vector>

namespace jac {

struct terrain;
struct textured_model;

class terrain_renderer {
public:
    terrain_renderer(const terrain_shader& shader, const glm::mat4& projection_matrix);

    void render(const terrain_list& terrains) const;

private:
    void load_model_matrix(const terrain& terrain) const;
    void prepare_terrain(const terrain& terrain) const;
    void unbind_textured_model() const;

    const terrain_shader& shader;
};

}

#endif
