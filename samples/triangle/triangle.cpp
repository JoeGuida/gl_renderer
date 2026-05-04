#include <print>

#include <spdlog/spdlog.h>

#include "input/input.hpp"
#include "window/window.hpp"
#include "renderer/api/gl_loader.hpp"
#include "renderer/core/logger.hpp"
#include "renderer/core/renderer.hpp"
#include "renderer/core/shader.hpp"
#include "renderer/object/primitive.hpp"
#include "renderer/settings/scene_settings.hpp"
#include "renderer/types/uint.hpp"
#include "renderer/util/errors.hpp"

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

    auto window = exit_on_error(initialize_window(instance, show_window, settings.width, settings.height, L"window class", L"Triangle"));

    Renderer renderer { .window_handle = window.handle.get() };
    exit_on_error(initialize_renderer(renderer));

    // Object Setup --------------------------------------------------------------------------------

    ObjectProperties properties {
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .material = {
            .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        }
    };

    add_primitive(Primitive::Triangle, properties, renderer);
    setup_draw(renderer);

    // Shader Setup --------------------------------------------------------------------------------

    Shader shader {
        .name = "triangle",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };

    auto id = exit_on_error(compile(shader, std::filesystem::current_path() / "samples" / "triangle"));

    // Input --------------------------------------------------------------------------------------

    setup_input_devices(window.handle->hwnd);

    InputBinding close_window {
        .keycode = KeyCode::Escape,
        .action = InputAction::Call,
        .trigger = KeyState::Pressed,
        .callback = [&window](){ DestroyWindow(window.handle->hwnd); }
    };

    bind(close_window);

    // Main Loop -----------------------------------------------------------------------------------

    auto draw_callback = [&renderer, &id]() {
        draw(renderer, id);
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw_callback);

    return EXIT_SUCCESS;
}
