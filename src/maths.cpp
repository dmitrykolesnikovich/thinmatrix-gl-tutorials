
#include "maths.hpp"

#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace jac {
namespace maths {

glm::mat4 create_transformation_matrix(const glm::vec3& translation,
                                       float rx, float ry, float rz,
                                       float scale)
{
    glm::mat4 matrix{};

    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3{1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3{0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3{0, 0, 1});
    matrix = glm::scale(matrix, glm::vec3{scale, scale, scale});

    return matrix;
}

glm::mat4 create_view_matrix(const camera& cam)
{
    glm::mat4 view_matrix{};

    view_matrix = glm::rotate(view_matrix, glm::radians(cam.get_pitch()), {1, 0, 0});
    view_matrix = glm::rotate(view_matrix, glm::radians(cam.get_yaw()), {0, 1, 0});
    view_matrix = glm::translate(view_matrix, -cam.get_position());

    return view_matrix;
}

float barrycentric(const glm::vec3& p1, const glm::vec3& p2,
                   const glm::vec3& p3, const glm::vec2& pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}


}
}


