cmake_minimum_required(VERSION 2.8)

project(jac C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${jac_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

find_package(SDL2 REQUIRED)

add_executable(jac
    src/display_manager.cpp
    src/glad.c
    src/loader.cpp
    src/main_game_loop.cpp
    src/raw_model.cpp
    src/renderer.cpp
)

target_include_directories(jac PRIVATE
    "${jac_SOURCE_DIR}/include"
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(jac PRIVATE
    ${SDL2_LIBRARY}
)

