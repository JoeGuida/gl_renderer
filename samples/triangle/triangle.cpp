#include <array>
#include <filesystem>
#include <print>
#include <variant>

#include <spdlog/spdlog.h>

#include <renderer/gl_loader.hpp>
#include <renderer/logger.hpp>
#include <renderer/primitive.hpp>
#include <renderer/renderer.hpp>
#include <renderer/shader.hpp>
#include <renderer/uint.hpp>
#include <renderer/vector.hpp>
#include <renderer/vertex.hpp>
#include <window/window.hpp>

constexpr u32 width = 1280; 
constexpr u32 height = 720;

int WinMain(HINSTANCE instance, HINSTANCE unused, LPSTR command_line, int show_window) {
    if(auto logger = init_logger(); !logger.has_value()) {
        std::println("could not initialize logger");
    }

    // initialize a win32 window
    auto window_handle = initialize_window(instance, show_window, width, height, L"window class", L"Triangle");
    if(!window_handle.has_value()) {
        spdlog::error(window_handle.error());
    }

    Window window {
        .width = width,
        .height = height,
        .handle = std::move(window_handle.value())
    };

#ifdef DEBUG
    // sometimes tools like RenderDoc need to be attached to the process before opengl is initialized
    MessageBoxA(nullptr, "Continue?", "Continue?", MB_OK);
#endif

    Renderer renderer { .window_handle = window.handle.get() };
    auto initialized = initialize_renderer(renderer);
    if(!initialized.has_value()) {
        spdlog::error(initialized.error());
    }

    ObjectProperties properties {
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .material = {
            .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        }
    };

    add_primitive(PrimitiveType::Triangle, properties, renderer);

    Shader shader {
        .name = "triangle",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };

    auto compiled_shader = compile(shader);
    if(!compiled_shader.has_value()) {
        spdlog::error(compiled_shader.error().message);
    }

    glEnable(GL_DEPTH_TEST);

    setup_draw(renderer);
    auto draw_callback = [&renderer, &compiled_shader]() {
        draw(renderer, compiled_shader.value());
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw_callback);
}
