
#include "loader.hpp"

#include "gl_handles.hpp"
#include "sdl_handles.hpp"

#include "SDL.h"

#include <stb_image.h>

namespace jac {

struct loader::pimpl {
    std::vector<gl::vertex_array_handle> vaos;
    std::vector<gl::buffer_handle> vbos;
    std::vector<gl::texture_handle> textures;

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
                                      int coord_size,
                                      const std::vector<float>& data)
    {
        GLuint vbo_id = create_vbo();
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float),
                     data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(attrib_num, coord_size, GL_FLOAT, GL_FALSE, 0, nullptr);

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
loader::load_to_vao(const std::vector<float>& positions,
                    const std::vector<float>& texture_coords,
                    const std::vector<int>& indices)
{
    auto vao_id = priv->create_vao();
    priv->bind_indices_buffer(indices);
    priv->store_data_in_attribute_list(0, 3, positions);
    priv->store_data_in_attribute_list(1, 2, texture_coords);
    priv->unbind_vao();
    raw_model model{vao_id, int(indices.size())};
    return model;
}

GLuint
loader::load_texture(const std::string& filename)
{
    int w, h, comp;
    auto data = stbi_load(("res/" + filename + ".png").c_str(), &w, &h, &comp,
                          STBI_rgb_alpha);
    SDL_assert(data != nullptr);

    gl::texture_handle texture;
    glGenTextures(1, &texture);
    GLuint texture_id = texture.get();
    priv->textures.push_back(std::move(texture));

    GLenum mode = comp == 4 ? GL_RGBA : GL_RGB;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode,
                 GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return texture_id;
}

}
