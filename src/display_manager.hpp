#ifndef JAC_DISPLAY_MANAGER_HPP
#define JAC_DISPLAY_MANAGER_HPP

#include "sdl_handles.hpp"

#include <chrono>

namespace jac {

using time_point = std::chrono::high_resolution_clock::time_point;
using seconds = std::chrono::duration<float, std::chrono::seconds::period>;

struct display {
    sdl_window_ptr window;
    sdl_gl_context gl_context;
};

display create_display();

void update_display(display& display);

seconds get_frame_time_seconds();

}

#endif
