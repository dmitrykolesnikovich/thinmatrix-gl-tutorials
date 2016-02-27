
#ifndef JAC_RAW_MODEL_HPP
#define JAC_RAW_MODEL_HPP

#include <functional>

namespace jac {

struct raw_model {
    unsigned vao_id;
    int vertex_count;
};

inline bool operator==(const raw_model& lhs, const raw_model& rhs)
{
    return lhs.vao_id == rhs.vao_id && lhs.vertex_count == rhs.vertex_count;
}

} // end namespace jac

namespace std {

template <>
struct hash<jac::raw_model> {
    using argument_type = jac::raw_model;
    using result_type = size_t;

    size_t operator()(const jac::raw_model& model) noexcept {
        return hash<unsigned>{}(model.vao_id) ^
        hash<int>{}(model.vertex_count);
    }
};

}


#endif
