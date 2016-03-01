
#include "entity.hpp"
#include "textured_model.hpp"

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

float entity::get_texture_x_offset() const
{
    int column = texture_index % model.texture.number_of_rows;
    return column/(float)model.texture.number_of_rows;
}

float entity::get_texture_y_offset() const
{
    int row = texture_index/model.texture.number_of_rows;
    return row/(float)model.texture.number_of_rows;
}


}

