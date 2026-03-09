#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <array>

#include <renderer/primitive.hpp>
#include <renderer/types.hpp>
#include <renderer/vertex.hpp>
#include <window/window.hpp>

struct Settings {
    static constexpr u32 object_count = 256;
};

struct Renderer {
    std::array<vec3, Settings::object_count> positions;
    std::array<vec3, Settings::object_count> colors;

    u32 object_index = 0;
};

std::expected<void, std::string> initialize_opengl(PlatformWindow* handle);

template <size_t N>
void add_primitive(Renderer& renderer, PrimitiveType type, const std::array<Vertex, N>& vertices) {
    for(const auto& i : vertices) {
        renderer.positions[renderer.object_index] = i.position;
        renderer.object_index++;
    }
}

#endif
