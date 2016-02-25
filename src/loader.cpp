
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

    auto create_vbo()
    {
        gl::buffer_handle vbo;
        glGenBuffers(1, &vbo);
        auto vbo_id = vbo.get();
        vbos.push_back(std::move(vbo));
        return vbo_id;
    }

    void store_data_in_attribute_list(GLuint attrib_num,
                                      const std::vector<float>& data)
    {
        GLuint vbo_id = create_vbo();
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

    void bind_indices_buffer(const std::vector<int>& indices)
    {
        GLuint vbo = create_vbo();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
                     indices.data(), GL_STATIC_DRAW);
    }
};

loader::loader() : priv{std::make_unique<pimpl>()} {}
loader::loader(loader&&) = default;
loader& loader::operator=(loader&&) = default;
loader::~loader() = default;

raw_model
loader::load_to_vao(const std::vector<float>& data,
                    const std::vector<int>& indices)
{
    auto vao_id = priv->create_vao();
    priv->bind_indices_buffer(indices);
    priv->store_data_in_attribute_list(0, data);
    priv->unbind_vao();
    raw_model model{vao_id, int(indices.size())};
    return model;
}

}
