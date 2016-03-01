#ifndef JAC_GUI_TEXTURE_HPP
#define JAC_GUI_TEXTURE_HPP

#include <glm/vec2.hpp>

namespace jac {

struct gui_texture {
    unsigned texture_id = 0;
    glm::vec2 position{};
    glm::vec2 scale{};
};

}

#endif
