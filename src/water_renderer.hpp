
#ifndef JAC_WATER_RENDERER_HPP
#define JAC_WATER_RENDERER_HPP

#include "raw_model.hpp"
#include "water_shader.hpp"

#include <vector>

namespace jac {

class loader;
struct water_tile;

class water_renderer {
public:
    water_renderer(jac::loader& loader,
                   water_shader shader,
                   const glm::mat4& projection_matrix);

    void render(const std::vector<water_tile>& water,
                const jac::camera& camera) const;

private:
    void prepare_render(const jac::camera& camera) const;
    void unbind() const;
    void set_up_vao(jac::loader& loader);

    raw_model quad{};
    water_shader shader{};
};

}

#endif //JAC_WATER_RENDERER_HPP
