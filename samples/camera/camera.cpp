#include <print>

#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

#include "input/input.hpp"
#include "window/window.hpp"
#include "renderer/api/gl_loader.hpp"
#include "renderer/core/camera.hpp"
#include "renderer/core/logger.hpp"
#include "renderer/core/renderer.hpp"
#include "renderer/core/shader.hpp"
#include "renderer/core/transform.hpp"
#include "renderer/object/primitive.hpp"
#include "renderer/settings/scene_settings.hpp"
#include "renderer/types/float.hpp"
#include "renderer/types/uint.hpp"
#include "renderer/util/errors.hpp"

void move_camera(Camera& camera) {
    camera.transform.position += vec3(0.0f, 0.0f, -1.0f) * 0.1f;
}

int WinMain(HINSTANCE instance, HINSTANCE unused, LPSTR command_line, int show_window) {
#ifdef DEBUG
    // sometimes tools like RenderDoc need to be attached to the process before opengl is initialized
    MessageBoxA(nullptr, "Continue?", "Continue?", MB_OK);
#endif

    // Renderer / Window Setup --------------------------------------------------------------------
    exit_on_error(init_logger());

    SceneSettings settings {
        .width = 1280,
        .height = 720
    };

    auto window = exit_on_error(initialize_window(instance, show_window, settings.width, settings.height, L"window class", L"Camera"));

    Renderer renderer { .window_handle = window.handle.get() };
    exit_on_error(initialize_renderer(renderer));

    // Object Setup -------------------------------------------------------------------------------

    ObjectProperties properties {
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .scale = glm::vec3(0.5f, 0.5f, 1.0f),
        .material = {
            .color = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f)
        }
    };

    add_primitive(Primitive::Cube, properties, renderer);

    Camera camera{
        .transform = Transform::Empty,
        .direction = vec3(0.0f, 0.0f, 1.0f),
        .aspect = settings.width / static_cast<f32>(settings.height),
        .fov = glm::radians(90.0f),
        .near = 0.01f,
        .far = 10.0f
    };

    auto projection = glm::perspective(camera.fov, camera.aspect, camera.near, camera.far);
    auto view = glm::lookAt(camera.transform.position, camera.transform.position + camera.direction, vec3(0.0f, 1.0f, 0.0f));

    // Shader Setup -------------------------------------------------------------------------------

    Shader shader {
        .name = "camera",
        .stages = { ShaderStage::Vertex, ShaderStage::Fragment }
    };

    auto compiled_shader = compile(shader, std::filesystem::current_path() / "samples" / "camera");
    if(!compiled_shader.has_value()) {
        spdlog::error(compiled_shader.error().message);
        return EXIT_FAILURE;
    }

    setup_draw(renderer);

    // Input --------------------------------------------------------------------------------------

    setup_input_devices(window.handle->hwnd);

    InputBinding close_window {
        .keycode = KeyCode::Escape,
        .action = InputAction::Call,
        .trigger = KeyState::Pressed,
        .callback = [&window](){ DestroyWindow(window.handle->hwnd); }
    };

    bind(close_window);

    // Main Loop ----------------------------------------------------------------------------------

    auto draw_callback = [&renderer, &compiled_shader]() {
        draw(renderer, compiled_shader.value());
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw_callback);

    return EXIT_SUCCESS;
}
