
#ifndef JAC_PLAYER_HPP
#define JAC_PLAYER_HPP

#include "entity.hpp"

namespace jac {

class terrain;

class player : public entity {
public:
    using entity::entity;

    void move(const terrain& terrain);
    void jump();
    void turn_left();
    void turn_right();
    void move_forward();
    void move_back();

private:
    void check_inputs();

    float current_speed = 0;
    float current_turn_speed = 0;
    float upwards_speed = 0;
    bool is_in_air = false;
};

}

#endif
