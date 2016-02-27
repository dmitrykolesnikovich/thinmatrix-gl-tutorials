#ifndef JAC_MODEL_TEXTURE_HPP
#define JAC_MODEL_TEXTURE_HPP

#include <functional>
#include <tuple>

namespace jac {

struct model_texture {
    unsigned texture_id = 0;
    float shine_damper = 1;
    float reflectivity = 0;
    bool has_transparency = false;
    bool use_fake_lighting = false;
};

inline bool operator==(const model_texture& lhs, const model_texture& rhs)
{
    return std::tie(lhs.texture_id, lhs.shine_damper, lhs.reflectivity) ==
            std::tie(rhs.texture_id, rhs.shine_damper, rhs.reflectivity);
}

}

namespace std {

template <>
struct hash<jac::model_texture> {
    using argument_type = jac::model_texture;
    using result_type = size_t;

    size_t operator()(const jac::model_texture& texture) noexcept {
        return hash<unsigned>{}(texture.texture_id) ^
                hash<float>{}(texture.shine_damper) ^
                hash<float>{}(texture.reflectivity);
    }
};
}

#endif
