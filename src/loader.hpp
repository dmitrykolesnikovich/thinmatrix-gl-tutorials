
#ifndef KTX_VIEWER_LOADER_HPP
#define KTX_VIEWER_LOADER_HPP

#include "raw_model.hpp"

#include <memory>
#include <string>
#include <vector>

namespace jac {

class loader {
public:
    loader();
    loader(loader&&);
    loader& operator=(loader&&);
    ~loader();

    raw_model load_to_vao(const std::vector<float>& data,
                          const std::vector<float>& texture_coords,
                          const std::vector<float>& normals,
                          const std::vector<int>& indices);

    GLuint load_texture(const std::string& filename);

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};

} // end namespace jac

#endif
