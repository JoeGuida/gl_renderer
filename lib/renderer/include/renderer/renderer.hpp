#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <expected>
#include <string>

#include <window/window.hpp>

#include <renderer/object_data.hpp>
#include <renderer/object_properties.hpp>
#include <renderer/primitive.hpp>
#include <renderer/uint.hpp>

struct Count {
    u32 triangle = 0;
    u32 quad = 0;
    u32 cube = 0;
};

struct Renderer {
    PlatformWindow* window_handle;
    ObjectData object_data;
    Count count;

    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 ubo;
};

void add_primitive(Primitive primitive, const ObjectProperties& properties, Renderer& renderer);
void draw(Renderer& renderer, u32 shader);
std::expected<void, std::string> initialize_opengl(PlatformWindow* handle);
std::expected<void, std::string> initialize_renderer(Renderer& renderer);
void setup_draw(Renderer& renderer);
void upload_ubo(Renderer& renderer);

#endif
