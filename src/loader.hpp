
#ifndef KTX_VIEWER_LOADER_HPP
#define KTX_VIEWER_LOADER_HPP

#include "raw_model.hpp"

#include <memory>
#include <vector>

namespace jac {

class loader {
public:
    loader();
    loader(loader&&);
    loader& operator=(loader&&);
    ~loader();

    raw_model load_to_vao(const std::vector<float>& data);

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};

} // end namespace jac

#endif
