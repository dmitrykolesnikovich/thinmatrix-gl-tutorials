#ifndef JAC_TERRAIN_HPP
#define JAC_TERRAIN_HPP

#include "model_texture.hpp"
#include "raw_model.hpp"

namespace jac {

class loader;

struct terrain {
    terrain(int grid_x, int grid_z, loader& loader,
            model_texture texture);

    float x;
    float z;
    raw_model model;
    model_texture texture;
};

}

#endif
