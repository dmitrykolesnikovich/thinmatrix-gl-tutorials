#ifndef JAC_TERRAIN_RENDERER_HPP
#define JAC_TERRAIN_RENDERER_HPP

#include <glm/mat4x4.hpp>

#include <vector>

namespace jac {

class terrain;
struct textured_model;
class terrain_shader;

class terrain_renderer {
public:
    terrain_renderer(const terrain_shader& shader, const glm::mat4& projection_matrix);

    void render(const std::vector<const terrain*>& terrains) const;

private:
    void load_model_matrix(const terrain& terrain) const;
    void prepare_terrain(const terrain& terrain) const;
    void bind_textures(const terrain& terrain) const;
    void unbind_textured_model() const;

    const terrain_shader& shader;
};

}

#endif
