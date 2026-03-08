#include <array>
#include <print>

#include <spdlog/spdlog.h>

#include <renderer/gl_loader.hpp>
#include <renderer/logger.hpp>
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

    // 
    u32 vao;
    u32 vbo;
    std::array<float, 9> vertices {
        -1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         1.0f, 0.0f, 0.0f
    };

    load_gl_functions();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto draw = [vao]() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw);
}
