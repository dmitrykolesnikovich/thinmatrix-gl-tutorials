
#ifndef KTX_VIEWER_LOADER_HPP
#define KTX_VIEWER_LOADER_HPP

#include "gl_handles.hpp"

#include <memory>
#include <string>
#include <vector>

namespace jac {

struct raw_model;

class loader {
public:
    raw_model load_to_vao(const std::vector<float>& data,
                          const std::vector<float>& texture_coords,
                          const std::vector<float>& normals,
                          const std::vector<int>& indices);

    raw_model load_to_vao(const std::vector<float>& positions);

    GLuint load_texture(const std::string& filename);

private:
    GLuint create_vao();
    GLuint create_vbo();
    void store_data_in_attribute_list(GLuint attrib_num,
                                      int coord_size,
                                      const std::vector<float>& data);
    void unbind_vao();
    void bind_indices_buffer(const std::vector<int>& indices);


    std::vector<gl::vertex_array_handle> vaos;
    std::vector<gl::buffer_handle> vbos;
    std::vector<gl::texture_handle> textures;
};

} // end namespace jac

#endif
