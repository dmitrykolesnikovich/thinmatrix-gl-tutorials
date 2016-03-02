
#include "camera.hpp"

#include "player.hpp"

#include "SDL.h"

#include <cmath>

namespace {

constexpr float to_radians(float degrees)
{
    return degrees * M_PI/180.0;
}

}

namespace jac {

void camera::move()
{
    calculate_zoom();
    calculate_pitch();
    calculate_angle_around_player();
    float horizontal_distance = calculate_horizontal_distance();
    float vertical_distance = calculate_vertical_distance();
    calculate_camera_position(horizontal_distance, vertical_distance);
    yaw = 180 - (player_.get_rot_y() + angle_around_player);
}

camera::camera(const player& player_)
    : player_{player_}
{}

const glm::vec3& camera::get_position() const
{
    return position;
}

float camera::get_pitch() const
{
    return pitch;
}

float camera::get_yaw() const
{
    return yaw;
}

float camera::get_roll() const
{
    return roll;
}

float camera::calculate_horizontal_distance()
{
    return distance_from_player * std::cos(to_radians(pitch));
}

float camera::calculate_vertical_distance()
{
    return distance_from_player * std::sin(to_radians(pitch));
}

void camera::calculate_camera_position(float horiz_distance,
                                       float vert_distance)
{
    float theta = player_.get_rot_y() + angle_around_player;
    float offset_x = horiz_distance * std::sin(to_radians(theta));
    float offset_z = horiz_distance * std::cos(to_radians(theta));
    position.x = player_.get_position().x - offset_x;
    position.y = player_.get_position().y + vert_distance;
    position.z = player_.get_position().z - offset_z;
}

void camera::calculate_zoom()
{
    float zoom_level = mouse_wheel_delta;
    distance_from_player -= zoom_level;
    mouse_wheel_delta = 0;
}

void camera::mouse_wheel(int delta)
{
    mouse_wheel_delta = delta;
}

void camera::calculate_pitch()
{
    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK) {
        float pitch_change = mouse_y_delta;
        pitch += pitch_change;
        mouse_y_delta = 0;
    }
}

void camera::calculate_angle_around_player()
{
    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK) {
        float angle_change = mouse_x_delta;
        angle_around_player -= angle_change;
        mouse_x_delta = 0;
    }
}

void camera::mouse_move(int dx, int dy)
{
    mouse_x_delta = 0.3 * dx;
    mouse_y_delta = 0.1 * dy;
}
}
