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
    static constexpr u32 vertex_offset = 0; // index of the first vertex in unified buffer

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
    static constexpr u32 vertex_offset = Triangle::vertex_count;

    static constexpr std::array<Vertex, vertex_count> vertices {
        Vertex{ .position = glm::vec3(-1.0f,  1.0f, 0.0f) },
        Vertex{ .position = glm::vec3( 1.0f,  1.0f, 0.0f) },
        Vertex{ .position = glm::vec3( 1.0f, -1.0f, 0.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f, 0.0f) }
    };

    static constexpr std::array<u32, index_count> indices {
        vertex_offset, 1 + vertex_offset, 2 + vertex_offset,
        vertex_offset, 2 + vertex_offset, 3 + vertex_offset
    };
};

struct Unified {
    static constexpr u32 vertex_count = Triangle::vertex_count + Quad::vertex_count;
    static constexpr std::array<Vertex, vertex_count> vertices {
        Triangle::vertices[0],
        Triangle::vertices[1],
        Triangle::vertices[2],
        Quad::vertices[0],
        Quad::vertices[1],
        Quad::vertices[2],
        Quad::vertices[3]
    };
};

#endif
