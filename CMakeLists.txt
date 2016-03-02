cmake_minimum_required(VERSION 2.8)

project(jac C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${jac_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

add_executable(jac
    src/camera.cpp
    src/display_manager.cpp
    src/entity.cpp
    src/entity_renderer.cpp
    src/glad.c
        src/gui_renderer.cpp
        src/gui_shader.cpp
        src/gui_texture.cpp
        src/light.cpp
    src/loader.cpp
    src/main_game_loop.cpp
    src/master_renderer.cpp
    src/maths.cpp
    src/model_texture.cpp
        src/mouse_picker.cpp
    src/obj_loader.cpp
    src/player.cpp
    src/raw_model.cpp
    src/shader_program.cpp
        src/skybox_renderer.cpp
        src/skybox_shader.cpp
    src/static_shader.cpp
    src/stb_image.c
    src/terrain.cpp
    src/terrain_renderer.cpp
    src/terrain_shader.cpp
    src/terrain_texture.cpp
    src/textured_model.cpp
    # This is just so the files appear in QtCreator
    src/shaders/vertex_shader.vert
    src/shaders/fragment_shader.frag
        src/shaders/gui_vertex_shader.vert
        src/shaders/gui_fragment_shader.frag
        src/shaders/skybox_vertex_shader.vert
        src/shaders/skybox_fragment_shader.frag
    src/shaders/terrain_vertex_shader.vert
    src/shaders/terrain_fragment_shader.frag
        src/water_frame_buffers.cpp
        src/water_renderer.cpp
        src/water_shader.cpp
        src/water_tile.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${jac_SOURCE_DIR}/res
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(jac PRIVATE
    "${jac_SOURCE_DIR}/include"
    ${GLM_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(jac PRIVATE
    ${SDL2_LIBRARY}
)

