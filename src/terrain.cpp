
#include "terrain.hpp"

#include "loader.hpp"
#include "sdl_handles.hpp"
#include "stb_image.hpp"
#include "maths.hpp"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <iostream>
#include <vector>

namespace {

constexpr float size = 800.0f;
constexpr float max_height = 40.0f;
constexpr std::uint32_t max_pixel_colour = 256 * 256 * 256;


float get_height(int x, int z, const stb::image& image)
{
    if (x < 0 || x > image.height() || z < 0 || z > image.height()) {
        return 0;
    }

    uint32_t val = image.get_rgb(x, z);

    double height = val;
    height /= (max_pixel_colour/2);
    height -= 1.0;
    height *= max_height;
    //std::cout << height << std::endl;

    return height;
}


glm::vec3 calculate_normal(int x, int z, const stb::image& image)
{
    float height_l = get_height(x - 1, z, image);
    float height_r = get_height(x + 1, z, image);
    float height_d = get_height(x, z - 1, image);
    float height_u = get_height(x, z + 1, image);

    glm::vec3 normal{height_l - height_r, 2.0f, height_d - height_u};
    normal = glm::normalize(normal);

    return normal;
}

} // end anonymous namespace





namespace jac {

terrain::terrain(int grid_x, int grid_z, loader& loader,
                 terrain_texture_pack texture_pack,
                 terrain_texture blend_map,
                 const std::string& heightmap)
    : x{grid_x * size},
      z{grid_z * size},
      model{generate_terrain(loader, heightmap)},
      texture_pack{std::move(texture_pack)},
      blend_map{std::move(blend_map)}
{}

jac::raw_model terrain::generate_terrain(jac::loader& loader,
                                         const std::string& heightmap)
{
    stb::image image{"res/" + heightmap + ".png", 4};
    int vertex_count = image.height();
    heights.resize(vertex_count);
    for (auto& h : heights) h.resize(vertex_count);

    int count = vertex_count * vertex_count;
    auto vertices = std::vector<float>(count * 3);
    auto normals = std::vector<float>(count * 3);
    auto textureCoords = std::vector<float>(count * 2);
    auto indices = std::vector<int>(6*(vertex_count-1)*(vertex_count-1));
    int vertexPointer = 0;

    for(int i=0;i<vertex_count;i++) {
        for(int j=0;j<vertex_count;j++){
            vertices[vertexPointer*3] = (float)j/((float)vertex_count - 1) * size;
            float height = get_height(j, i, image);
            heights[j][i] = height;
            vertices[vertexPointer*3+1] = height;
            vertices[vertexPointer*3+2] = (float)i/((float)vertex_count - 1) * size;
            auto normal = calculate_normal(j, i, image);
            normals[vertexPointer*3] = normal.x;
            normals[vertexPointer*3+1] = normal.y;
            normals[vertexPointer*3+2] = normal.z;
            textureCoords[vertexPointer*2] = (float)j/((float)vertex_count - 1);
            textureCoords[vertexPointer*2+1] = (float)i/((float)vertex_count - 1);
            vertexPointer++;
        }
    }
    int pointer = 0;
    for(int gz=0;gz<vertex_count-1;gz++){
        for(int gx=0;gx<vertex_count-1;gx++){
            int topLeft = (gz*vertex_count)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*vertex_count)+gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    return loader.load_to_vao(vertices, textureCoords, normals, indices);
}

float terrain::get_height_of_terrain(float world_x, float world_z) const
{
    float terrain_x = world_x - x;
    float terrain_z = world_z - z;
    float grid_square_size = size/(float) (heights.size() - 1);
    int grid_x = std::floor(terrain_x/grid_square_size);
    int grid_z = std::floor(terrain_z/grid_square_size);
    if (grid_x > heights.size() - 1 || grid_z > heights.size() - 1 ||
            grid_x < 0 || grid_z < 0) {
        return 0;
    }

    float x_coord = std::fmod(terrain_x, grid_square_size)/grid_square_size;
    float z_coord = std::fmod(terrain_z, grid_square_size)/grid_square_size;
    float answer = 0.0f;

    if (x_coord <= (1 - z_coord)) {
        answer = maths::barrycentric(
                glm::vec3{0, heights[grid_x][grid_z], 0},
                glm::vec3{1, heights[grid_x + 1][grid_z], 0},
                glm::vec3{0, heights[grid_x][grid_z + 1], 1},
                glm::vec2{x_coord, z_coord});
    } else {
        answer = maths::barrycentric(
                glm::vec3{0, heights[grid_x + 1][grid_z], 0},
                glm::vec3{1, heights[grid_x + 1][grid_z + 1], 1},
                glm::vec3{0, heights[grid_x][grid_z + 1], 1},
                glm::vec2{x_coord, z_coord});
    }

    return answer;
}

}

