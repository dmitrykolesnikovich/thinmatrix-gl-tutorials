#ifndef JAC_MASTER_RENDERER_HPP
#define JAC_MASTER_RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <vector>

namespace jac {

struct camera;
struct entity;
struct light;
struct terrain;
struct textured_model;

using terrain_list = std::vector<const terrain*>;
using entity_map = std::unordered_map<textured_model, std::vector<const entity*>>;

class master_renderer
{
public:
    master_renderer();
    master_renderer(master_renderer&&);
    master_renderer& operator=(master_renderer&&);
    ~master_renderer();

    void prepare() const;

    void render(const light& sun, const camera& cam) const;

    void process_entity(const entity& entity);
    void process_terrain(const terrain& terrain);

    static void enable_culling();
    static void disable_culling();

private:
    struct pimpl;
    std::unique_ptr<pimpl> priv;
};


}

#endif
