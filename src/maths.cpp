
#include "maths.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace jac {

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

    view_matrix = glm::rotate(view_matrix, glm::radians(cam.pitch), {1, 0, 0});
    view_matrix = glm::rotate(view_matrix, glm::radians(cam.yaw), {0, 1, 0});
    view_matrix = glm::translate(view_matrix, -cam.position);

    return view_matrix;
}

}


