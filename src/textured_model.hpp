#ifndef JAC_TEXTURED_MODEL_HPP
#define JAC_TEXTURED_MODEL_HPP

#include "model_texture.hpp"
#include "raw_model.hpp"

#include <functional>
#include <tuple>

namespace jac {

struct textured_model {
    raw_model raw{};
    model_texture texture{};
};

inline bool operator==(const textured_model& lhs, const textured_model& rhs)
{
    return lhs.raw == rhs.raw && lhs.texture == rhs.texture;
}

}

namespace std {

template <>
struct hash<jac::textured_model> {
    using argument_type = jac::textured_model;
    using result_type = size_t;

    size_t operator()(const jac::textured_model& model) const noexcept {
        return hash<jac::raw_model>{}(model.raw) ^
        hash<jac::model_texture>{}(model.texture);
    }
};

}

#endif
