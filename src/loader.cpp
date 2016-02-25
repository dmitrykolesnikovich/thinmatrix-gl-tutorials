
#include "loader.hpp"

#include "gl_handles.hpp"

namespace jac {

struct loader::pimpl {
    std::vector<gl::vertex_array_handle> vaos;
    std::vector<gl::buffer_handle> vbos;

    auto create_vao()
    {
        gl::vertex_array_handle vao;
        glGenVertexArrays(1, &vao);
        auto vao_id = vao.get();
        glBindVertexArray(vao_id);
        vaos.push_back(std::move(vao));
        return vao_id;
    }

    void store_data_in_attribute_list(GLuint attrib_num,
                                      const std::vector<float>& data)
    {
        {
            gl::buffer_handle vbo;
            glGenBuffers(1, &vbo);
            vbos.push_back(std::move(vbo));
        }
        GLuint vbo_id = vbos.back().get();
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float),
                     data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(attrib_num, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void unbind_vao()
    {
        glBindVertexArray(0);
    }
};

loader::loader() : priv{std::make_unique<pimpl>()} {}
loader::loader(loader&&) = default;
loader& loader::operator=(loader&&) = default;
loader::~loader() = default;

raw_model
loader::load_to_vao(const std::vector<float>& data)
{
    auto vao_id = priv->create_vao();
    priv->store_data_in_attribute_list(0, data);
    priv->unbind_vao();
    raw_model model{vao_id, int(data.size()/3)};
    return model;
}

}
