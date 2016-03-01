#ifndef JAC_MATHS_HPP
#define JAC_MATHS_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace jac {

class camera;

namespace maths {

float barrycentric(const glm::vec3& p1,
                   const glm::vec3& p2,
                   const glm::vec3& p3,
                   const glm::vec2& pos);

glm::mat4 create_transformation_matrix(const glm::vec3& translation,
                                       float rx, float ry, float rz,
                                       float scale);

glm::mat4 create_transformation_matrix(const glm::vec2& translation,
                                       const glm::vec2& scale);

glm::mat4 create_view_matrix(const camera& cam);

}
}

#endif
