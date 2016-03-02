#ifndef JAC_WATER_TILE_HPP
#define JAC_WATER_TILE_HPP

namespace jac {

struct water_tile {
    float x = 0;
    float z = 0;
    float height = 0;

    static constexpr float tile_size = 60.0f;
};

}

#endif //JAC_WATER_TILE_HPP
