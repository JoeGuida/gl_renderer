cmake_minimum_required(VERSION 4.0)
project(renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(spdlog CONFIG REQUIRED)

add_library(renderer STATIC
    src/gl_loader.cpp
    src/logger.cpp
    src/shader.cpp
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(renderer spdlog::spdlog_header_only)
