
#ifndef JAC_RENDERER_HPP
#define JAC_RENDERER_HPP

#include "raw_model.hpp"

namespace jac {

class renderer {
public:
    void prepare();

    void render(const raw_model& model);
};


}

#endif
