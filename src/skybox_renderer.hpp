
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

    void render(const camera& cam, float r, float g, float b);

private:
    void bind_textures();

    raw_model cube{};
    unsigned texture_id = 0;
    unsigned night_texture_id = 0;
    skybox_shader shader{};
    float time = 0.0f;
};

}

#endif
