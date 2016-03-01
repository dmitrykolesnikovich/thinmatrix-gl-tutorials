#ifndef JAC_ENTITY_HPP
#define JAC_ENTITY_HPP

#include "textured_model.hpp"

#include <glm/vec3.hpp>

namespace jac {

class entity {
public:
    entity(const textured_model &model, const glm::vec3 &position, float rot_x,
           float rot_y, float rot_z, float scale)
            : model(model),
              position(position),
              rot_x(rot_x), rot_y(rot_y),
              rot_z(rot_z),
              scale(scale)
    {}

    entity(const textured_model &model, int index,
           const glm::vec3 &position, float rot_x,
           float rot_y, float rot_z, float scale)
            : model(model),
              position(position),
              rot_x(rot_x), rot_y(rot_y),
              rot_z(rot_z),
              scale(scale),
              texture_index(index)
    {}

    void increase_position(float dx, float dy, float dz);
    void increase_rotation(float dx, float dy, float dz);

    const textured_model& get_model() const { return model; }
    const glm::vec3& get_position() const { return position; }
    float get_rot_x() const { return rot_x; }
    float get_rot_y() const { return rot_y; }
    float get_rot_z() const { return rot_z; }
    float get_scale() const { return scale; }
    float get_texture_x_offset() const;
    float get_texture_y_offset() const;

protected:
    textured_model model{};
    glm::vec3 position{};
    float rot_x = 0.0f;
    float rot_y = 0.0f;
    float rot_z = 0.0f;
    float scale = 0.0f;

private:
    int texture_index = 0;
};


}

#endif
