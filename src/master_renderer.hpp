#ifndef JAC_MASTER_RENDERER_HPP
#define JAC_MASTER_RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <vector>

namespace jac {

struct camera;
struct entity;
struct light;
struct textured_model;

using entity_map = std::unordered_map<textured_model, std::vector<const entity*>>;

class master_renderer
{
public:
    master_renderer();
    master_renderer(master_renderer&&);
    master_renderer& operator=(master_renderer&&);
    ~master_renderer();

    void render(const light& sun, const camera& cam) const;

    void process_entity(const entity& entity);

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};


}

#endif
