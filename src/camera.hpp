#ifndef JAC_CAMERA_HPP
#define JAC_CAMERA_HPP

#include <glm/vec3.hpp>

namespace jac {

struct camera {
    glm::vec3 position{100.0f, 35.0f, 50.0f};
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;

    void move();
};


}

#endif
