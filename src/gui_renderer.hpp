#ifndef JAC_GUI_RENDERER_HPP
#define JAC_GUI_RENDERER_HPP

#include "raw_model.hpp"
#include "gui_shader.hpp"

#include <vector>

namespace jac {

class loader;
struct gui_texture;

class gui_renderer {
public:
    gui_renderer(loader& loader);

    void render(const std::vector<gui_texture>& guis) const;

private:
    const raw_model quad;
    gui_shader shader{};
};

}

#endif
