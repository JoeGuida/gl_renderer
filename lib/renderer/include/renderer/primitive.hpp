#ifndef RENDERER_PRIMITIVE_HPP
#define RENDERER_PRIMITIVE_HPP

#include <array>

#include <renderer/uint.hpp>
#include <renderer/vertex.hpp>

enum class PrimitiveType : u32 {
    Line,
    LineStrip,
    Point,
    Quad,
    Triangle,
    TriangleStrip,
};

template<PrimitiveType T>
struct PrimitiveTraits;

template<>
struct PrimitiveTraits<PrimitiveType::Quad> {
    static constexpr u32 vertex_count = 4;
    static constexpr u32 index_count = 6;
    static constexpr std::array<Vertex, vertex_count> vertices {
        Vertex{ .position = glm::vec3(-1.0f,  1.0f, 0.0f), .color = glm::vec3(0.0f) },
        Vertex{ .position = glm::vec3( 1.0f,  1.0f, 0.0f), .color = glm::vec3(0.0f) },
        Vertex{ .position = glm::vec3( 1.0f, -1.0f, 0.0f), .color = glm::vec3(0.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f, 0.0f), .color = glm::vec3(0.0f) }
    };
    static constexpr std::array<u32, index_count> indices {
        0, 1, 2,
        2, 3, 0
    };
};

template<>
struct PrimitiveTraits<PrimitiveType::Triangle> {
    static constexpr u32 vertex_count = 3;
    static constexpr u32 index_count = 3;
    static constexpr std::array<Vertex, vertex_count> vertices {
        Vertex{ .position = glm::vec3(-1.0f,  0.0f, 0.0f), .color = glm::vec3(0.0f) },
        Vertex{ .position = glm::vec3( 1.0f,  0.0f, 0.0f), .color = glm::vec3(0.0f) },
        Vertex{ .position = glm::vec3( 0.0f,  1.0f, 0.0f), .color = glm::vec3(0.0f) }
    };
    static constexpr std::array<u32, index_count> indices {
        0, 1, 2,
    };
};

#endif
