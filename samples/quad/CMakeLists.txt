cmake_minimum_required(VERSION 4.0)

find_package(spdlog CONFIG REQUIRED)

add_executable(quad WIN32
    quad.cpp
)

target_compile_definitions(quad PRIVATE DEBUG)

target_link_libraries(quad PRIVATE
    engine
    spdlog::spdlog_header_only
    opengl32.lib
)
