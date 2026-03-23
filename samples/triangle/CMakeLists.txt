cmake_minimum_required(VERSION 4.0)

find_package(spdlog CONFIG REQUIRED)

add_executable(triangle WIN32
    triangle.cpp
)

target_compile_definitions(triangle PRIVATE DEBUG)

target_link_libraries(triangle PRIVATE
    engine
    spdlog::spdlog_header_only
    opengl32.lib
)
