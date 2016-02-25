
#ifndef JAC_RENDERER_HPP
#define JAC_RENDERER_HPP

#include "textured_model.hpp"

namespace jac {

class renderer {
public:
    void prepare();

    void render(const textured_model& tex_model);
};


}

#endif
