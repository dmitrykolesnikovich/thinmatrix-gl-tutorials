#ifndef JAC_OBJ_LOADER_HPP
#define JAC_OBJ_LOADER_HPP

#include "loader.hpp"
#include "raw_model.hpp"

#include <string>

namespace jac {

raw_model load_obj_model(const std::string& filename,
                         loader& loader);

}

#endif
