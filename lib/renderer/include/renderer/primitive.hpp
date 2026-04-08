#ifndef RENDERER_PRIMITIVE_HPP
#define RENDERER_PRIMITIVE_HPP

#include <array>

#include <renderer/settings.hpp>
#include <renderer/uint.hpp>
#include <renderer/vector.hpp>
#include <renderer/vertex.hpp>

enum class Primitive : u32 {
    Triangle,
    Quad,
    Cube
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
        vertex_offset + 0, vertex_offset + 1, vertex_offset + 2,
        vertex_offset + 0, vertex_offset + 2, vertex_offset + 3
    };
};

struct Cube {
    static constexpr u32 vertex_count = 24;
    static constexpr u32 index_count = 36;
    static constexpr u32 offset = Settings::object_count * 2;
    static constexpr u32 vertex_offset = Triangle::vertex_count + Quad::vertex_count;

    static constexpr std::array<Vertex, vertex_count> vertices {
        Vertex{ .position = glm::vec3(-1.0f,  1.0f, -1.0f) }, // front
        Vertex{ .position = glm::vec3( 1.0f,  1.0f, -1.0f) },
        Vertex{ .position = glm::vec3( 1.0f, -1.0f, -1.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f, -1.0f) },

        Vertex{ .position = glm::vec3(1.0f,  1.0f, -1.0f) }, // right
        Vertex{ .position = glm::vec3(1.0f,  1.0f,  1.0f) },
        Vertex{ .position = glm::vec3(1.0f, -1.0f,  1.0f) },
        Vertex{ .position = glm::vec3(1.0f, -1.0f, -1.0f) },

        Vertex{ .position = glm::vec3(-1.0f,  1.0f, 1.0f) }, // back
        Vertex{ .position = glm::vec3( 1.0f,  1.0f, 1.0f) },
        Vertex{ .position = glm::vec3( 1.0f, -1.0f, 1.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f, 1.0f) },

        Vertex{ .position = glm::vec3(-1.0f,  1.0f, -1.0f) }, // left
        Vertex{ .position = glm::vec3(-1.0f,  1.0f,  1.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f,  1.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f, -1.0f) },

        Vertex{ .position = glm::vec3(-1.0f, 1.0f,  1.0f) }, // top
        Vertex{ .position = glm::vec3( 1.0f, 1.0f,  1.0f) },
        Vertex{ .position = glm::vec3( 1.0f, 1.0f, -1.0f) },
        Vertex{ .position = glm::vec3(-1.0f, 1.0f, -1.0f) },

        Vertex{ .position = glm::vec3(-1.0f, -1.0f,  1.0f) }, // bottom
        Vertex{ .position = glm::vec3( 1.0f, -1.0f,  1.0f) },
        Vertex{ .position = glm::vec3( 1.0f, -1.0f, -1.0f) },
        Vertex{ .position = glm::vec3(-1.0f, -1.0f, -1.0f) }
    };

    static constexpr std::array<u32, index_count> indices {
        vertex_offset +  0, vertex_offset +  1, vertex_offset +  2,
        vertex_offset +  0, vertex_offset +  2, vertex_offset +  3,
        vertex_offset +  4, vertex_offset +  5, vertex_offset +  6,
        vertex_offset +  4, vertex_offset +  6, vertex_offset +  7,
        vertex_offset +  8, vertex_offset +  9, vertex_offset + 10,
        vertex_offset +  8, vertex_offset + 10, vertex_offset + 11,
        vertex_offset + 12, vertex_offset + 13, vertex_offset + 14,
        vertex_offset + 12, vertex_offset + 14, vertex_offset + 15,
        vertex_offset + 16, vertex_offset + 17, vertex_offset + 18,
        vertex_offset + 16, vertex_offset + 18, vertex_offset + 19,
        vertex_offset + 20, vertex_offset + 21, vertex_offset + 22,
        vertex_offset + 20, vertex_offset + 22, vertex_offset + 23
    };
};

struct Unified {
    static constexpr u32 vertex_count = Triangle::vertex_count + Quad::vertex_count + Cube::vertex_count;
    static constexpr u32 index_count = Quad::index_count + Cube::index_count;
    static constexpr std::array<Vertex, vertex_count> vertices {
        Triangle::vertices[0],
        Triangle::vertices[1],
        Triangle::vertices[2],

        Quad::vertices[0],
        Quad::vertices[1],
        Quad::vertices[2],
        Quad::vertices[3],

        Cube::vertices[0],
        Cube::vertices[1],
        Cube::vertices[2],
        Cube::vertices[3],
        Cube::vertices[4],
        Cube::vertices[5],
        Cube::vertices[6],
        Cube::vertices[7],
        Cube::vertices[8],
        Cube::vertices[9],
        Cube::vertices[10],
        Cube::vertices[11],
        Cube::vertices[12],
        Cube::vertices[13],
        Cube::vertices[14],
        Cube::vertices[15],
        Cube::vertices[16],
        Cube::vertices[17],
        Cube::vertices[18],
        Cube::vertices[19],
        Cube::vertices[20],
        Cube::vertices[21],
        Cube::vertices[22],
        Cube::vertices[23]
    };
    static constexpr std::array<u32, index_count> indices {
        Quad::vertex_offset + 0, Quad::vertex_offset + 1, Quad::vertex_offset + 2,
        Quad::vertex_offset + 0, Quad::vertex_offset + 2, Quad::vertex_offset + 3,

        Cube::vertex_offset +  0, Cube::vertex_offset +  1, Cube::vertex_offset +  2,
        Cube::vertex_offset +  0, Cube::vertex_offset +  2, Cube::vertex_offset +  3,
        Cube::vertex_offset +  4, Cube::vertex_offset +  5, Cube::vertex_offset +  7,
        Cube::vertex_offset +  4, Cube::vertex_offset +  6, Cube::vertex_offset +  7,
        Cube::vertex_offset +  8, Cube::vertex_offset +  9, Cube::vertex_offset + 11,
        Cube::vertex_offset +  8, Cube::vertex_offset + 10, Cube::vertex_offset + 11,
        Cube::vertex_offset + 12, Cube::vertex_offset + 13, Cube::vertex_offset + 15,
        Cube::vertex_offset + 12, Cube::vertex_offset + 14, Cube::vertex_offset + 15,
        Cube::vertex_offset + 16, Cube::vertex_offset + 17, Cube::vertex_offset + 19,
        Cube::vertex_offset + 16, Cube::vertex_offset + 18, Cube::vertex_offset + 19,
        Cube::vertex_offset + 20, Cube::vertex_offset + 21, Cube::vertex_offset + 23,
        Cube::vertex_offset + 20, Cube::vertex_offset + 22, Cube::vertex_offset + 23
    };
};

#endif
