
#ifndef JAC_RENDERER_HPP
#define JAC_RENDERER_HPP

#include "entity.hpp"
#include "static_shader.hpp"

#include <memory>

namespace jac {

class renderer {
public:
    explicit renderer(const static_shader& shader);
    renderer(renderer&&);
    renderer& operator=(renderer&&);
    ~renderer();

    void prepare();

    void render(const entity& entity, static_shader& shader);

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};


}

#endif
