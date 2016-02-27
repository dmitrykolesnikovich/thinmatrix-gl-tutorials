
#ifndef JAC_RENDERER_HPP
#define JAC_RENDERER_HPP

#include "master_renderer.hpp"

namespace jac {

class static_shader;

class renderer {
public:
    explicit renderer(const static_shader& shader);
    renderer(renderer&&);
    renderer& operator=(renderer&&);
    ~renderer();

    void prepare();

    void render(const entity_map& entities) const;

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};


}

#endif
