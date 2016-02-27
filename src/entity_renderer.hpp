
#ifndef JAC_RENDERER_HPP
#define JAC_RENDERER_HPP

#include "master_renderer.hpp"

#include <glm/mat4x4.hpp>

namespace jac {

class static_shader;

class entity_renderer {
public:
    explicit entity_renderer(const static_shader& shader,
                             const glm::mat4& projection_matrix);
    entity_renderer(entity_renderer&&);
    entity_renderer& operator=(entity_renderer&&);
    ~entity_renderer();

    void render(const entity_map& entities) const;

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};


}

#endif
