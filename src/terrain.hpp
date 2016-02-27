#ifndef JAC_TERRAIN_HPP
#define JAC_TERRAIN_HPP

#include "raw_model.hpp"
#include "terrain_texture.hpp"

namespace jac {

class loader;

struct terrain {
    terrain(int grid_x, int grid_z, loader& loader,
            terrain_texture_pack texture_pack,
            terrain_texture blend_map);

    float x;
    float z;
    raw_model model;
    terrain_texture_pack texture_pack;
    terrain_texture blend_map;
};

}

#endif
