#include <print>

#include <spdlog/spdlog.h>

#include "window/window.hpp"

#include "renderer/api/gl_loader.hpp"
#include "renderer/core/logger.hpp"
#include "renderer/core/renderer.hpp"
#include "renderer/core/shader.hpp"
#include "renderer/object/primitive.hpp"
#include "renderer/types/uint.hpp"

int WinMain(HINSTANCE instance, HINSTANCE unused, LPSTR command_line, int show_window) {
#ifdef DEBUG
    // sometimes tools like RenderDoc need to be attached to the process before opengl is initialized
    MessageBoxA(nullptr, "Continue?", "Continue?", MB_OK);
#endif

    // Renderer / Window Setup ---------------------------------------------------------------------

    exit_on_error(init_logger());

    SceneSettings settings {
        .width = 1280,
        .height = 720
    };

    auto window = exit_on_error(initialize_window(instance, show_window, settings.width, settings.height, L"window class", L"Quad"));

    Renderer renderer { .window_handle = window.handle.get() };
    exit_on_error(initialize_renderer(renderer));

    // Object Setup --------------------------------------------------------------------------------

    ObjectProperties properties {
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .material = {
            .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        }
    };

    add_primitive(Primitive::Quad, properties, renderer);

    // Shader Setup --------------------------------------------------------------------------------

    Shader shader {
        .name = "quad",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };

    auto compiled_shader = compile(shader, std::filesystem::current_path() / "samples" / "quad");
    if(!compiled_shader.has_value()) {
        spdlog::error(compiled_shader.error().message);
        return EXIT_FAILURE;
    }

    setup_draw(renderer);

    // Main Loop -----------------------------------------------------------------------------------

    auto draw_callback = [&renderer, &compiled_shader]() {
        draw(renderer, compiled_shader.value());
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw_callback);

    return EXIT_SUCCESS;
}
