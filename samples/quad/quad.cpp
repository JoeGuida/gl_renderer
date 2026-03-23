#include <print>

#include <spdlog/spdlog.h>

#include <renderer/gl_loader.hpp>
#include <renderer/logger.hpp>
#include <renderer/primitive.hpp>
#include <renderer/renderer.hpp>
#include <renderer/shader.hpp>
#include <renderer/uint.hpp>
#include <window/window.hpp>

constexpr u32 width = 1280; 
constexpr u32 height = 720;

int WinMain(HINSTANCE instance, HINSTANCE unused, LPSTR command_line, int show_window) {
    if(auto logger = init_logger(); !logger.has_value()) {
        std::println("could not initialize logger");
        return EXIT_FAILURE;
    }

    auto init_window = initialize_window(instance, show_window, width, height, L"window class", L"Quad");
    if(!init_window.has_value()) {
        spdlog::error(init_window.error());
        return EXIT_FAILURE;
    }
    Window& window = init_window.value();

#ifdef DEBUG
    // sometimes tools like RenderDoc need to be attached to the process before opengl is initialized
    MessageBoxA(nullptr, "Continue?", "Continue?", MB_OK);
#endif

    Renderer renderer { .window_handle = window.handle.get() };
    auto initialized = initialize_renderer(renderer);
    if(!initialized.has_value()) {
        spdlog::error(initialized.error());
        return EXIT_FAILURE;
    }

    ObjectProperties properties {
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .material = {
            .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        }
    };

    add_primitive(PrimitiveType::Quad, properties, renderer);

    Shader shader {
        .name = "flat_shading",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };

    auto result = add_shader(renderer, shader);
    if(!result.has_value()) {
        spdlog::error(result.error().message);
        return EXIT_FAILURE;
    }

    u32& id = result.value();
    setup_draw(renderer);
    auto draw_callback = [&renderer, &id]() {
        draw(renderer, id);
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw_callback);

    return EXIT_SUCCESS;
}
