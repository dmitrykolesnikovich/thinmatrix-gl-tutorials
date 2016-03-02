
#ifndef JAC_SKYBOX_RENDERER_HPP
#define JAC_SKYBOX_RENDERER_HPP

#include "raw_model.hpp"
#include "skybox_shader.hpp"

namespace jac {

class loader;

class skybox_renderer
{
public:
    skybox_renderer(loader& loader, const glm::mat4& matrix);

    void render(const camera& cam) const;

private:
    raw_model cube{};
    unsigned texture_id;
    skybox_shader shader{};
};

}

#endif
