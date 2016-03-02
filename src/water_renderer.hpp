
#ifndef JAC_WATER_RENDERER_HPP
#define JAC_WATER_RENDERER_HPP

#include "raw_model.hpp"
#include "water_shader.hpp"
#include "water_frame_buffers.hpp"

#include <vector>

namespace jac {

class loader;
struct water_tile;
class water_frame_buffers;

class water_renderer {
public:
    water_renderer(jac::loader& loader,
                   water_shader shader,
                   const glm::mat4& projection_matrix,
                   const water_frame_buffers& fbos);

    void render(const std::vector<water_tile>& water,
                const jac::camera& camera);

private:
    void prepare_render(const jac::camera& camera);
    void unbind() const;
    void set_up_vao(jac::loader& loader);

    raw_model quad{};
    water_shader shader{};
    const water_frame_buffers& fbos;
    GLuint dudv_texture = 0;
    float move_factor = 0;
};

}

#endif //JAC_WATER_RENDERER_HPP
