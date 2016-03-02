
#ifndef JAC_MOUSE_PICKER_HPP
#define JAC_MOUSE_PICKER_HPP

#include "camera.hpp"

#include <glm/mat4x4.hpp>

namespace jac {

class mouse_picker {
public:
    mouse_picker(const camera& cam, const glm::mat4& projection);

    const glm::vec3& get_current_ray() const { return current_ray; }

    void update();

private:
    glm::vec3 calculate_mouse_ray();

    const camera& cam;
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;
    glm::vec3 current_ray;
};

}

#endif //JAC_MOUSE_PICKER_HPP
