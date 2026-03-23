cmake_minimum_required(VERSION 4.0)

find_package(spdlog CONFIG REQUIRED)

add_executable(cube WIN32
    cube.cpp
)

target_compile_definitions(cube PRIVATE DEBUG)

target_link_libraries(cube PRIVATE
    engine
    spdlog::spdlog_header_only
    opengl32.lib
)
