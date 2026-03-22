#ifndef RENDERER_PRIMITIVE_HPP
#define RENDERER_PRIMITIVE_HPP

#include <array>

#include <renderer/settings.hpp>
#include <renderer/uint.hpp>
#include <renderer/vector.hpp>
#include <renderer/vertex.hpp>

enum class PrimitiveType : u32 {
    Triangle,
    Quad
};

struct Triangle {
    static constexpr u32 vertex_count = 3;
    static constexpr u32 offset = 0;

    static constexpr std::array<Vertex, vertex_count> vertices {
        Vertex{ .position = glm::vec3(-0.5f, -0.5f, 0.0f) },
        Vertex{ .position = glm::vec3( 0.5f, -0.5f, 0.0f) },
        Vertex{ .position = glm::vec3( 0.0f,  0.5f, 0.0f) }
    };
};

struct Quad {
    static constexpr u32 vertex_count = 4;
    static constexpr u32 index_count = 6;
    static constexpr u32 offset = Settings::object_count;

    static constexpr std::array<Vertex, vertex_count> vertices {
        Vertex{ .position = glm::vec3( -1.0f,  1.0f, 0.0f) },
        Vertex{ .position = glm::vec3(  1.0f,  1.0f, 0.0f) },
        Vertex{ .position = glm::vec3(  1.0f, -1.0f, 0.0f) },
        Vertex{ .position = glm::vec3( -1.0f, -1.0f, 0.0f) }
    };

    static constexpr std::array<u32, index_count> indices {
        0, 1, 2,
        0, 2, 3
    };
};

#endif
