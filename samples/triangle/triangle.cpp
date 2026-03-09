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
#include <renderer/types.hpp>
#include <renderer/vertex.hpp>
#include <window/window.hpp>

constexpr uint32_t width = 1280; 
constexpr uint32_t height = 720;

int WinMain(HINSTANCE instance, HINSTANCE unused, LPSTR command_line, int show_window) {
    if(auto logger = init_logger(); !logger.has_value()) {
        std::println("could not initialize logger");
    }

    // initialize a win32 window
    auto window_handle = initialize_window(instance, show_window, width, height, L"window class", L"renderer");
    if(!window_handle.has_value()) {
        spdlog::error(window_handle.error());
    }

    Window window {
        .width = width,
        .height = height,
        .handle = std::move(window_handle.value())
    };

    auto gl_initialized = initialize_opengl(window.handle.get());
    if(!gl_initialized.has_value()) {
        spdlog::error(gl_initialized.error());
    }

    u32 vao;
    u32 vbo;
    u32 ubo;
    std::array<Vertex, 3> vertices {
        Vertex { .position = vec3(-0.5f, -0.5f, 0.0f), .color = vec3(0.0f, 1.0f, 0.0f) },
        Vertex { .position = vec3( 0.0f,  0.5f, 0.0f), .color = vec3(0.0f, 0.0f, 1.0f) },
        Vertex { .position = vec3( 0.5f, -0.5f, 0.0f), .color = vec3(1.0f, 0.0f, 0.0f) }
    };

    Renderer renderer;
    add_primitive(renderer, PrimitiveType::Triangle, vertices);

    std::filesystem::path shader_path = std::filesystem::current_path() / "shaders";

    // compile_shader has variant error types so we need to std::visit to print all of them
    Shader shader {
        .name = "triangle",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };

    auto compiled = compile_shader(shader);

    auto vertex_shader = compile_shader(shader_path, "triangle", ShaderStage::Vertex);
    if(!vertex_shader.has_value()) {
        auto& error = vertex_shader.error();
        std::visit([](auto&& error) {
            spdlog::error("{}", error.message);
        }, error);
    }

    auto fragment_shader = compile_shader(shader_path, "triangle", ShaderStage::Fragment);
    if(!fragment_shader.has_value()) {
        auto& error = fragment_shader.error();
        std::visit([](auto&& error) {
            spdlog::error("{}", error.message);
        }, error);
    }

    auto shader = link_shaders(vertex_shader.value(), fragment_shader.value());
    if(!shader.has_value()) {
        spdlog::error("{}", shader.error().message);
    }
    u32 shader_program = shader.value();

    u32 color_offset = renderer.object_index;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(vec3) * Settings::object_count, renderer.positions.data());
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(vec3) * Settings::object_count, sizeof(vec3) * Settings::object_count, renderer.colors.data());

    glEnable(GL_DEPTH_TEST);

    auto draw = [vao, shader_program]() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        glUseProgram(shader_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw);
}
