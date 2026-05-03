cmake_minimum_required(VERSION 4.0)
project(input)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(spdlog CONFIG REQUIRED)

add_library(input STATIC
    src/input.cpp
)

target_include_directories(input PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(input spdlog::spdlog_header_only)
