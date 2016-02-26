
#include "entity.hpp"

namespace jac {

void entity::increase_position(float dx, float dy, float dz)
{
    position += glm::vec3(dx, dy, dz);
}

void entity::increase_rotation(float dx, float dy, float dz)
{
    rot_x += dx;
    rot_y += dy;
    rot_z += dz;
}

}

