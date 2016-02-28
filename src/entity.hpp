#ifndef JAC_ENTITY_HPP
#define JAC_ENTITY_HPP

#include "textured_model.hpp"

#include <glm/vec3.hpp>

namespace jac {

struct entity {


    entity(const textured_model &model, const glm::vec3 &position, float rot_x,
           float rot_y, float rot_z, float scale) : model(model),
                                                    position(position),
                                                    rot_x(rot_x), rot_y(rot_y),
                                                    rot_z(rot_z),
                                                    scale(scale) { }

    textured_model model{};
    glm::vec3 position{};
    float rot_x = 0.0f;
    float rot_y = 0.0f;
    float rot_z = 0.0f;
    float scale = 0.0f;

    void increase_position(float dx, float dy, float dz);
    void increase_rotation(float dx, float dy, float dz);
};


}

#endif
