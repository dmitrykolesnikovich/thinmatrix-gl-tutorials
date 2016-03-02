#ifndef JAC_CAMERA_HPP
#define JAC_CAMERA_HPP

#include <glm/vec3.hpp>

namespace jac {

class player;

class camera {
public:
    camera(const player& player);

    const glm::vec3& get_position() const;
    void set_position(const glm::vec3& pos) { position = pos; }
    float get_pitch() const;
    float get_yaw() const;
    float get_roll() const;
    void move();
    void mouse_wheel(int delta);
    void mouse_move(int dx, int dy);
    void invert_pitch() { pitch = -pitch; }

private:
    void calculate_zoom();
    void calculate_pitch();
    void calculate_angle_around_player();
    float calculate_horizontal_distance();
    float calculate_vertical_distance();

    const player& player_;
    glm::vec3 position{100.0f, 35.0f, 50.0f};
    float pitch = 25.0f;
    float yaw = 0.0f;
    float roll = 0.0f;
    float distance_from_player = 50.0f;
    float angle_around_player = 0;

    int mouse_wheel_delta = 0;
    int mouse_x_delta = 0;
    int mouse_y_delta = 0;

    void calculate_camera_position(float horiz_distance, float vert_distance);
};


}

#endif
