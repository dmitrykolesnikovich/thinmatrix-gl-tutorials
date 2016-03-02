
#include "mouse_picker.hpp"
#include "maths.hpp"

#include "SDL.h"

#include <glm/vec2.hpp>
#include <glm/matrix.hpp>

namespace {

glm::vec2 get_normalised_device_coords(float mouse_x, float mouse_y)
{
    int w, h;
    SDL_Window* win = SDL_GL_GetCurrentWindow();
    SDL_assert(win);
    SDL_GetWindowSize(win, &w, &h);

    float x = (2.0f * mouse_x)/(float)w - 1.0f;
    float y = (2.0f * mouse_y)/(float)h - 1.0f;

    return {x, -y};
}

glm::vec4 to_eye_coords(const glm::vec4& clip_coords, const glm::mat4& proj_mat)
{
    glm::vec4 eye_coords = glm::inverse(proj_mat) * clip_coords;
    return { eye_coords.x, eye_coords.y, -1.0, 0.0};
}

glm::vec3 to_world_coords(const glm::vec4& eye_coords, const glm::mat4& view_mat)
{
    auto mouse_ray = glm::vec3{glm::inverse(view_mat) * eye_coords};
    return normalize(mouse_ray);
}

}


namespace jac {

mouse_picker::mouse_picker(const camera& cam, const glm::mat4& projection)
    : cam{cam},
      projection_matrix{projection},
      view_matrix{maths::create_view_matrix(cam)}
{}

void mouse_picker::update()
{
    view_matrix = maths::create_view_matrix(cam);
    current_ray = calculate_mouse_ray();
}

glm::vec3 mouse_picker::calculate_mouse_ray()
{
    float mouse_x = 0;
    float mouse_y = 0;

    {
        int imouse_x, imouse_y;
        SDL_GetMouseState(&imouse_x, &imouse_y);
        mouse_x = imouse_x; mouse_y = imouse_y;
    }

    auto normalized_coords = get_normalised_device_coords(mouse_x, mouse_y);
    auto clip_coords = glm::vec4(normalized_coords, -1.0f, 1.0f);
    auto eye_coords = to_eye_coords(clip_coords, projection_matrix);
    auto world_ray = to_world_coords(eye_coords, view_matrix);

    return world_ray;
}


}
