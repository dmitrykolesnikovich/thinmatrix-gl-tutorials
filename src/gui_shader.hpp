#ifndef JAC_GUI_SHADER_HPP
#define JAC_GUI_SHADER_HPP

#include "shader_program.hpp"

namespace jac {

class gui_shader final : public shader_program
{
public:
    gui_shader();

    void load_transformation(const glm::mat4& matrix) const;

private:
    virtual void bind_attributes() override;
    virtual void get_all_uniform_locations() override;

    int location_transformation_matrix = 0;
};

}

#endif
