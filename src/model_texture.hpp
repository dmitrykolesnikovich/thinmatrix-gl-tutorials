#ifndef JAC_MODEL_TEXTURE_HPP
#define JAC_MODEL_TEXTURE_HPP

#include <memory>

namespace jac {

struct model_texture {
    unsigned texture_id = 0;
    float shine_damper = 1;
    float reflectivity = 0;
};

}

#endif
