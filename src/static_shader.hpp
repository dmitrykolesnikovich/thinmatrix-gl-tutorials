#ifndef JAC_STATIC_SHADER_HPP
#define JAC_STATIC_SHADER_HPP

#include "shader_program.hpp"

#include "camera.hpp"
#include "light.hpp"

#include <glm/mat4x4.hpp>

namespace jac {

class static_shader final : public shader_program
{
public:
    static_shader();

    static_shader(static_shader&&);
    static_shader& operator=(static_shader&&);
    virtual ~static_shader();

    void load_transformation_matrix(const glm::mat4& matrix) const;
    void load_projection_matrix(const glm::mat4& projection) const;
    void load_view_matrix(const camera& camera) const;
    void load_light(const light& light) const;
    void load_shine_variables(float damper, float reflectivity) const;
    void load_fake_lighting_variable(bool use_fake) const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    struct pimpl;
    std::unique_ptr<pimpl> priv;
};


}

#endif
