
#include "obj_loader.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <algorithm>
#include <fstream>
#include <vector>

namespace {

// http://tcbrindle.github.io/posts/a-quicker-study-on-tokenising/
std::vector<std::string>
split(const std::string& str, const std::string& delims = " ",
      bool skip_empty = true)
{
    std::vector<std::string> output;
    auto first = std::cbegin(str);

    while (first != std::cend(str)) {
        const auto second = std::find_first_of(first, std::cend(str),
                                               std::cbegin(delims), std::cend(delims));
        if (first != second || !skip_empty) {
            output.emplace_back(first, second);
        }
        if (second == std::cend(str)) break;
        first =  std::next(second);
    }

    return output;
}

bool
starts_with(const std::string& str, const std::string& prefix)
{
    auto p = std::mismatch(std::cbegin(prefix), std::cend(prefix),
                           std::cbegin(str), std::cend(str));

    return p.first == std::cend(prefix);
}

}

namespace jac {

raw_model load_obj_model(const std::string& filename,
                         loader& loader)
{
    std::ifstream file{"res/" + filename + ".obj"};
    //file.exceptions(std::ios::badbit | std::ios::failbit);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;
    std::vector<int> indices;

    std::vector<float> vertices_array;
    std::vector<float> texture_array;
    std::vector<float> normals_array;

    std::string line;

    while (true) {
        std::getline(file, line);
        if (line.empty()) {
            continue;
        }

        auto current_line = split(line);
        if (starts_with(line, "v ")) {
            vertices.emplace_back(std::stof(current_line.at(1)),
                                  std::stof(current_line.at(2)),
                                  std::stof(current_line.at(3)));
        }
        else if (starts_with(line, "vt ")) {
            textures.emplace_back(std::stof(current_line.at(1)),
                                 std::stof(current_line.at(2)));
        }
        else if (starts_with(line, "vn ")) {
            normals.emplace_back(std::stof(current_line.at(1)),
                                 std::stof(current_line.at(2)),
                                 std::stof(current_line.at(3)));
        }
        else if (starts_with(line, "f ")) {
            texture_array.resize(vertices.size() * 2);
            normals_array.resize(vertices.size() * 3);
            break;
        }
    }

    while (!line.empty()) {
        if (!starts_with(line, "f ")) {
            std::getline(file, line);
            continue;
        }

        auto current_line = split(line);
        auto vertex1 = split(current_line.at(1), "/");
        auto vertex2 = split(current_line.at(2), "/");
        auto vertex3 = split(current_line.at(3), "/");

        auto process_vertex = [&] (const auto& vertex_data) {
            int current_vertex_pointer = std::stoi(vertex_data.at(0)) - 1;
            indices.push_back(current_vertex_pointer);

            glm::vec2 current_tex = textures.at(std::stoi(vertex_data.at(1)) - 1);
            texture_array.at(current_vertex_pointer * 2) = current_tex.x;
            texture_array.at(current_vertex_pointer * 2 + 1) = 1.0f - current_tex.y;

            glm::vec3 current_norm = normals.at(std::stoi(vertex_data.at(2)) - 1);
            normals_array.at(current_vertex_pointer * 3) = current_norm.x;
            normals_array.at(current_vertex_pointer * 3 + 1) = current_norm.y;
            normals_array.at(current_vertex_pointer * 3 + 2) = current_norm.z;
        };

        process_vertex(vertex1);
        process_vertex(vertex2);
        process_vertex(vertex3);

        std::getline(file, line);
    }

    // Will this function never end...

    vertices_array.reserve(vertices.size() * 3);

    for (const auto& vertex : vertices) {
        vertices_array.push_back(vertex.x);
        vertices_array.push_back(vertex.y);
        vertices_array.push_back(vertex.z);
    }

    return loader.load_to_vao(vertices_array, texture_array, normals_array, indices);
}


}

