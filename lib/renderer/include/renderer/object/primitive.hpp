#ifndef RENDERER_OBJECT_PRIMITIVE_HPP
#define RENDERER_OBJECT_PRIMITIVE_HPP

#include <array>

#include "renderer/core/vertex.hpp"
#include "renderer/settings/renderer_settings.hpp"
#include "renderer/types/uint.hpp"
#include "renderer/types/vec.hpp"

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
    static constexpr u32 offset = RendererSettings::object_count;
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
    static constexpr u32 offset = RendererSettings::object_count * 2;
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
    static constexpr u32 cube_index(auto i) {
        return Cube::vertex_offset + i;
    }

    static constexpr u32 quad_index(auto i) {
        return Quad::vertex_offset + i;
    }

    // combines all primitive arrays into one unified array
    template<typename T, size_t... N>
    static constexpr auto concat_arrays(const std::array<T, N>&... arrs) {
        constexpr size_t size = (N + ...);
        std::array<T, size> result{};

        size_t offset = 0;

        auto copy = [&](const auto& arr) {
            for(size_t i = 0; i < arr.size(); i++) {
                result[offset + i] = arr[i];
            }
            offset += arr.size();
        };

        (copy(arrs), ...);

        return result;
    }

    static constexpr u32 vertex_count = Triangle::vertex_count + Quad::vertex_count + Cube::vertex_count;
    static constexpr u32 index_count = Quad::index_count + Cube::index_count;
    static constexpr std::array<Vertex, vertex_count> vertices = concat_arrays(Triangle::vertices, Quad::vertices, Cube::vertices);
    static constexpr std::array<u32, index_count> indices = concat_arrays(Quad::indices, Cube::indices);
};

#endif
