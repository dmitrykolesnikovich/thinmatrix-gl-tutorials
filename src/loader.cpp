
#include "loader.hpp"

#include "gl_handles.hpp"
#include "raw_model.hpp"
#include "sdl_handles.hpp"
#include "stb_image.hpp"

#include "SDL.h"

namespace jac {

GLuint loader::create_vao()
{
    gl::vertex_array_handle vao;
    glGenVertexArrays(1, &vao);
    auto vao_id = vao.get();
    glBindVertexArray(vao_id);
    vaos.push_back(std::move(vao));
    return vao_id;
}

GLuint loader::create_vbo()
{
    gl::buffer_handle vbo;
    glGenBuffers(1, &vbo);
    auto vbo_id = vbo.get();
    vbos.push_back(std::move(vbo));
    return vbo_id;
}

void loader::store_data_in_attribute_list(GLuint attrib_num,
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

void loader::unbind_vao()
{
    glBindVertexArray(0);
}

void loader::bind_indices_buffer(const std::vector<int>& indices)
{
    GLuint vbo = create_vbo();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
                 indices.data(), GL_STATIC_DRAW);
}

raw_model
loader::load_to_vao(const std::vector<float>& positions,
                    const std::vector<float>& texture_coords,
                    const std::vector<float>& normals,
                    const std::vector<int>& indices)
{
    auto vao_id = create_vao();
    bind_indices_buffer(indices);
    store_data_in_attribute_list(0, 3, positions);
    store_data_in_attribute_list(1, 2, texture_coords);
    store_data_in_attribute_list(2, 3, normals);
    unbind_vao();
    raw_model model{vao_id, int(indices.size())};
    return model;
}

GLuint
loader::load_texture(const std::string& filename)
{
    stb::image image("res/" + filename + ".png");
    SDL_assert(image);

    gl::texture_handle texture;
    glGenTextures(1, &texture);
    GLuint texture_id = texture.get();
    textures.push_back(std::move(texture));

    GLenum mode = (image.num_components() == 4 ? GL_RGBA : GL_RGB);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, image.width(), image.height(), 0, mode,
                 GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return texture_id;
}

raw_model loader::load_to_vao(const std::vector<float>& positions,
                              int dimensions)
{
    GLuint vao_id = create_vao();
    store_data_in_attribute_list(0, dimensions, positions);
    unbind_vao();
    return raw_model{vao_id, int(positions.size()/dimensions)};
}

GLuint loader::load_cube_map(const std::vector<std::string>& texture_files)
{
    gl::texture_handle texture;
    glGenTextures(1, &texture);
    auto tex_id = texture.get();
    textures.push_back(std::move(texture));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);

    for (int i = 0; i < texture_files.size(); i++) {
        auto image = stb::image("res/" + texture_files[i] + ".png", 4);
        SDL_assert(image);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                     image.width(), image.height(), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return tex_id;
}


}
