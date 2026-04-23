cmake_minimum_required(VERSION 4.0)
project(renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(spdlog CONFIG REQUIRED)

add_library(renderer STATIC
    src/convert.cpp
    src/gl_loader.cpp
    src/logger.cpp
    src/renderer.cpp
    src/shader.cpp
    src/transform.cpp
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/opengl
)

target_link_libraries(renderer opengl32 window spdlog::spdlog_header_only)
