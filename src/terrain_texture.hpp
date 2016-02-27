
#ifndef JAC_TERRAIN_TEXTURE_HPP
#define JAC_TERRAIN_TEXTURE_HPP

#include "gl_handles.hpp"

namespace jac {

struct terrain_texture {
    //gl::texture_handle texture;
    unsigned texture_id;
};

struct terrain_texture_pack {
    terrain_texture background_texture;
    terrain_texture r_texture;
    terrain_texture g_texture;
    terrain_texture b_texture;
};

}

#endif
