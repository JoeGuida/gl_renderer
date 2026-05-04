cmake_minimum_required(VERSION 4.0)
project(input)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(input STATIC src/input.cpp src/scancode.cpp src/keycode.cpp)

target_compile_definitions(input PUBLIC
    UNICODE
    _UNICODE
)

target_include_directories(input PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(input PRIVATE spdlog::spdlog_header_only)

