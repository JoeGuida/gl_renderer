cmake_minimum_required(VERSION 4.0)

find_package(spdlog CONFIG REQUIRED)

add_executable(camera WIN32
    camera.cpp
)

target_compile_definitions(camera PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(camera PRIVATE
    engine
    spdlog::spdlog_header_only
    opengl32.lib
)
