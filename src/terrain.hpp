#ifndef JAC_TERRAIN_HPP
#define JAC_TERRAIN_HPP

#include "raw_model.hpp"
#include "terrain_texture.hpp"

#include <string>
#include <vector>

namespace jac {

class loader;

class terrain {
public:
    terrain(int grid_x, int grid_z, loader& loader,
            terrain_texture_pack texture_pack,
            terrain_texture blend_map,
            const std::string& heightmap);

    float get_x() const { return x; }
    float get_z() const { return z; }
    const raw_model& get_model() const { return model; }
    const terrain_texture_pack& get_texture_pack() const { return texture_pack; }
    const terrain_texture& get_blend_map() const { return blend_map; }

    float get_height_of_terrain(float world_x, float world_y) const;

private:
    raw_model generate_terrain(loader& loader, const std::string& heightmap);

    float x;
    float z;
    std::vector<std::vector<float>> heights;
    raw_model model;
    terrain_texture_pack texture_pack;
    terrain_texture blend_map;
};

}

#endif
