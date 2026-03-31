#include <print>

#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>

#include <window/window.hpp>
#include <renderer/camera.hpp>
#include <renderer/gl_loader.hpp>
#include <renderer/logger.hpp>
#include <renderer/primitive.hpp>
#include <renderer/renderer.hpp>
#include <renderer/shader.hpp>
#include <renderer/transform.hpp>
#include <renderer/uint.hpp>

constexpr u32 width = 1280; 
constexpr u32 height = 720;

int WinMain(HINSTANCE instance, HINSTANCE unused, LPSTR command_line, int show_window) {
#ifdef DEBUG
    // sometimes tools like RenderDoc need to be attached to the process before opengl is initialized
    MessageBoxA(nullptr, "Continue?", "Continue?", MB_OK);
#endif

    if(auto logger = init_logger(); !logger.has_value()) {
        std::println("could not initialize logger");
        return EXIT_FAILURE;
    }

    auto init_window = initialize_window(instance, show_window, width, height, L"window class", L"Camera");
    if(!init_window.has_value()) {
        spdlog::error(init_window.error());
        return EXIT_FAILURE;
    }
    Window& window = init_window.value();

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

    add_primitive(PrimitiveType::Cube, properties, renderer);

    Camera camera{
        .transform = Transform::Empty,
        .direction = vec3(0.0f, 0.0f, 1.0f),
        .aspect = width / static_cast<float>(height),
        .fov = 90.0f,
        .near = 0.01f,
        .far = 10.0f
    };

    auto projection = glm::perspective(camera.fov, camera.aspect, camera.near, camera.far);
    auto view = glm::lookAt(camera.transform.position, camera.transform.position + camera.direction, vec3(0.0f, 1.0f, 0.0f));

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
    auto draw_callback = [&renderer, &compiled_shader]() {
        draw(renderer, compiled_shader.value());
    };

    spdlog::info("running window");
    run_window(window.handle.get(), draw_callback);

    return EXIT_SUCCESS;
}
