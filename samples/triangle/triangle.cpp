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

    auto gl_initialized = initialize_opengl(window.handle.get());
    if(!gl_initialized.has_value()) {
        spdlog::error(gl_initialized.error());
    }

    u32 vao;
    u32 vbo;
    u32 ubo;
    std::array<Vertex, 3> vertices {
        Vertex { .position = glm::vec3(-0.5f, -0.5f, 0.0f), .color = glm::vec3(0.0f, 1.0f, 0.0f) },
        Vertex { .position = glm::vec3( 0.0f,  0.5f, 0.0f), .color = glm::vec3(0.0f, 0.0f, 1.0f) },
        Vertex { .position = glm::vec3( 0.5f, -0.5f, 0.0f), .color = glm::vec3(1.0f, 0.0f, 0.0f) }
    };

    Renderer renderer;
    add_primitive(renderer, PrimitiveType::Triangle, vertices);

    std::filesystem::path shader_path = std::filesystem::current_path() / "shaders";

    // compile_shader has variant error types so we need to std::visit to print all of them
    Shader shader {
        .name = "triangle",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };
    auto compiled_shader = compile(shader);

    if(!compiled_shader.has_value()) {
        spdlog::error(compiled_shader.error().message);
    }

    u32 color_offset = renderer.object_index;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ubo);

    glBindVertexArray(vao);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(vec3_std140) * Settings::object_count * 2, nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(vec3_std140) * Settings::object_count, renderer.positions.data());
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(vec3_std140) * Settings::object_count, sizeof(vec3_std140) * Settings::object_count, renderer.colors.data());
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

    glEnable(GL_DEPTH_TEST);

    auto draw = [vao, compiled_shader]() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        glUseProgram(compiled_shader.value());
        glDrawArrays(GL_TRIANGLES, 0, 3);
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw);
}
