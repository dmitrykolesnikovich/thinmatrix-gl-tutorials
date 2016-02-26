#ifndef JAC_LIGHT_HPP
#define JAC_LIGHT_HPP

#include <glm/vec3.hpp>

namespace jac {

struct light {
    glm::vec3 position;
    glm::vec3 colour;
};

}

#endif
