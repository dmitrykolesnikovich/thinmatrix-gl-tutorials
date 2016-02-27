
#ifndef JAC_RENDERER_HPP
#define JAC_RENDERER_HPP

#include "entity.hpp"

#include <glm/mat4x4.hpp>
#include <unordered_map>
#include <vector>

namespace jac {

struct entity;
class static_shader;
struct textured_model;

class entity_renderer {
public:
    using entity_map = std::unordered_map<textured_model, std::vector<const entity*>>;

    explicit entity_renderer(const static_shader& shader,
                             const glm::mat4& projection_matrix);

    void render(const entity_map& entities) const;

private:
    void prepare_textured_model(const jac::textured_model& model) const;
    void prepare_instance(const entity& entity) const;
    void unbind_textured_model() const;

    glm::mat4 projection_matrix;
    const static_shader& shader;
};


}

#endif
