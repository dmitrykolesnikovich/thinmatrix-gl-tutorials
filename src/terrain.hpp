#ifndef JAC_TERRAIN_HPP
#define JAC_TERRAIN_HPP

#include "raw_model.hpp"
#include "terrain_texture.hpp"

#include <string>

namespace jac {

class loader;

struct terrain {
    terrain(int grid_x, int grid_z, loader& loader,
            terrain_texture_pack texture_pack,
            terrain_texture blend_map,
            const std::string& heightmap);

    float x;
    float z;
    raw_model model;
    terrain_texture_pack texture_pack;
    terrain_texture blend_map;
};

}

#endif
