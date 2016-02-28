
#ifndef JAC_PLAYER_HPP
#define JAC_PLAYER_HPP

#include "entity.hpp"

namespace jac {

struct player : entity {
    using entity::entity;

    void move();

private:
    void check_inputs();
    void jump();

    float current_speed = 0;
    float current_turn_speed = 0;
    float upwards_speed = 0;
    bool is_in_air = false;
};

}

#endif
