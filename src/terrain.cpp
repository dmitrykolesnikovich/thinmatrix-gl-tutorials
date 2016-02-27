
#include "terrain.hpp"

#include "loader.hpp"

#include <vector>

namespace {

constexpr float size = 800;
constexpr int vertex_count = 128;

jac::raw_model generate_terrain(jac::loader& loader){
    int count = vertex_count * vertex_count;
    auto vertices = std::vector<float>(count * 3);
    auto normals = std::vector<float>(count * 3);
    auto textureCoords = std::vector<float>(count * 2);
    auto indices = std::vector<int>(6*(vertex_count-1)*(vertex_count-1));
    int vertexPointer = 0;

    for(int i=0;i<vertex_count;i++) {
            for(int j=0;j<vertex_count;j++){
                vertices[vertexPointer*3] = (float)j/((float)vertex_count - 1) * size;
                vertices[vertexPointer*3+1] = 0;
                vertices[vertexPointer*3+2] = (float)i/((float)vertex_count - 1) * size;
                normals[vertexPointer*3] = 0;
                normals[vertexPointer*3+1] = 1;
                normals[vertexPointer*3+2] = 0;
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


} // end anonymous namespace

namespace jac {

terrain::terrain(int grid_x, int grid_z, loader& loader,
                 model_texture texture)
    : x{grid_x * size},
      z{grid_z * size},
      model{generate_terrain(loader)},
      texture{std::move(texture)}
{}



}

