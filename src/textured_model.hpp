#ifndef JAC_TEXTURED_MODEL_HPP
#define JAC_TEXTURED_MODEL_HPP

#include "model_texture.hpp"
#include "raw_model.hpp"

namespace jac {

struct textured_model {
    raw_model raw{};
    model_texture texture{};
};


}

#endif
