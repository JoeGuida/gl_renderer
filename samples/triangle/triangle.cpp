#include <array>
#include <filesystem>
#include <print>
#include <variant>

#include <spdlog/spdlog.h>

#include <renderer/gl_loader.hpp>
#include <renderer/logger.hpp>
#include <renderer/renderer.hpp>
#include <renderer/shader.hpp>
#include <renderer/types.hpp>
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
    std::array<float, 18> vertices {
        // position         // color
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    std::filesystem::path shader_path = std::filesystem::current_path() / "shaders";

    // compile_shader has variant error types so we need to std::visit to print all of them
    auto vertex_shader = compile_shader(shader_path, "triangle", ShaderType::Vertex);
    if(!vertex_shader.has_value()) {
        auto& error = vertex_shader.error();
        std::visit([](auto&& error) {
            spdlog::error("{}", error.message);
        }, error);
    }

    auto fragment_shader = compile_shader(shader_path, "triangle", ShaderType::Fragment);
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

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
