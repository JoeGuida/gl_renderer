#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <array>
#include <expected>

#include <renderer/object_data.hpp>
#include <renderer/object_properties.hpp>
#include <renderer/primitive.hpp>
#include <renderer/settings.hpp>
#include <renderer/uint.hpp>
#include <renderer/vector.hpp>
#include <renderer/vertex.hpp>
#include <window/window.hpp>

struct Indices {
    u32 triangle;
    u32 quad;
};

struct Renderer {
    PlatformWindow* window_handle;

    ObjectData<PrimitiveType::Quad> quad_data;
    ObjectData<PrimitiveType::Triangle> triangle_data;
    Indices indices;

    u32 vao;
    u32 ubo;
};

std::expected<void, std::string> initialize_renderer(Renderer& renderer);
std::expected<void, std::string> initialize_opengl(PlatformWindow* handle);
void setup_draw(Renderer& renderer);
void draw(Renderer& renderer, u32 shader);
void add_primitive(const ObjectProperties& properties, Renderer& renderer);
bool can_add(PrimitiveType type, const Renderer& renderer);

#endif
