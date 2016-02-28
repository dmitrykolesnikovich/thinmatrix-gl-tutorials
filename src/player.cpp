
#include "player.hpp"

#include "display_manager.hpp"

#include "SDL.h"

#include <cmath>

constexpr float run_speed = 20;
constexpr float turn_speed = 160;
constexpr float gravity = -50;
constexpr float jump_power = 30;

constexpr float terrain_height = 0;


constexpr float to_radians(float degrees) {
    return degrees * M_PI/180.0;
}

namespace jac {

void player::move() {
    check_inputs();
    increase_rotation(0, current_turn_speed * get_frame_time_seconds().count(),
                    0);
    const auto distance = current_speed * get_frame_time_seconds().count();
    const auto dx = distance * std::sin(to_radians(rot_y));
    const auto dz = distance * std::cos(to_radians(rot_y));
    increase_position(dx, 0, dz);

    upwards_speed += gravity * get_frame_time_seconds().count();
    increase_position(0, upwards_speed * get_frame_time_seconds().count(), 0);

    if (position.y < terrain_height) {
        upwards_speed = 0;
        is_in_air = false;
        position.y = terrain_height;
    }
}

void player::check_inputs() {
    auto state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_W]) {
        current_speed = run_speed;
    } else if (state[SDL_SCANCODE_D]) {
        current_speed = -run_speed;
    } else {
        current_speed = 0;
    }

    if (state[SDL_SCANCODE_D]) {
        current_turn_speed = -turn_speed;
    } else if (state[SDL_SCANCODE_A]) {
        current_turn_speed = turn_speed;
    } else {
        current_turn_speed = 0;
    }

    if (state[SDL_SCANCODE_SPACE]) {
        jump();
        is_in_air = true;
    }
}

void player::jump() {
    if (!is_in_air) {
        upwards_speed += jump_power;
    }
}

}
