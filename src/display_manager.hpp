#ifndef JAC_DISPLAY_MANAGER_HPP
#define JAC_DISPLAY_MANAGER_HPP

#include "sdl_handles.hpp"

namespace jac {

struct display {
    sdl_window_ptr window;
    sdl_gl_context gl_context;
};

display create_display();

void update_display(display& display);

}

#endif
