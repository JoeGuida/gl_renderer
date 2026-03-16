#include <renderer/renderer.hpp>

#include <window/win32.hpp>

#include <renderer/gl_loader.hpp>
#include <renderer/wglext.h>

std::expected<void, std::string> initialize_renderer(Renderer& renderer) {
    auto opengl = initialize_opengl(renderer.window_handle);
    if(!opengl.has_value()) {
        return std::unexpected(opengl.error());
    }

    glGenVertexArrays(1, &renderer.vao);
    glGenBuffers(1, &renderer.ubo);

    return {};
}

std::expected<void, std::string> initialize_opengl(PlatformWindow* handle) {
    PIXELFORMATDESCRIPTOR pfd {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE
    };

    int pixel_format = ChoosePixelFormat(handle->hdc, &pfd);
    if(!pixel_format) {
        return std::unexpected("error choosing pixel format!");
    }
    if(!SetPixelFormat(handle->hdc, pixel_format, &pfd)) {
        return std::unexpected("error setting pixel format!");
    }

    int attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC temp_context = wglCreateContext(handle->hdc);
    wglMakeCurrent(handle->hdc, temp_context);
    load_wglCreateContextAttribsARB();

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(temp_context);

    HGLRC hglrc = wglCreateContextAttribsARB(handle->hdc, nullptr, attribs);
    if(!hglrc) {
        return std::unexpected("error creating gl context");
    }

    if(!wglMakeCurrent(handle->hdc, hglrc)) {
        return std::unexpected("failed to make gl context current");
    }

    load_gl_functions();

    handle->hglrc = hglrc;
    return {};
}

void setup_draw(Renderer& renderer) {
    glBindVertexArray(renderer.vao);
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubo);
    glBufferData(GL_UNIFORM_BUFFER, Settings::buffer_size * Settings::buffer_count, nullptr, GL_DYNAMIC_DRAW);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, Settings::buffer_size, renderer.triangle_data.positions.data());
    glBufferSubData(GL_UNIFORM_BUFFER, Settings::buffer_size, Settings::buffer_size, renderer.triangle_data.colors.data());
    glBufferSubData(GL_UNIFORM_BUFFER, Settings::buffer_size * 2, Settings::buffer_size, renderer.quad_data.positions.data());
    glBufferSubData(GL_UNIFORM_BUFFER, Settings::buffer_size * 3, Settings::buffer_size, renderer.quad_data.colors.data());

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, renderer.ubo);
}

void draw(Renderer& renderer, u32 shader) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(renderer.vao);
    glUseProgram(shader);
    glDrawElementsInstanced(GL_TRIANGLES, renderer.triangle_data.indices.size(), GL_UNSIGNED_INT, renderer.triangle_data.indices.data(), renderer.indices.triangle);
    glDrawElementsInstanced(GL_TRIANGLES, renderer.quad_data.indices.size(), GL_UNSIGNED_INT, renderer.quad_data.indices.data(), renderer.indices.quad);
}

void add_primitive(const ObjectProperties& properties, Renderer& renderer) {
    switch(properties.type) {
        case PrimitiveType::Triangle: {
            if(can_add(properties.type, renderer)) {
                renderer.triangle_data.positions[renderer.indices.triangle] = properties.position;
                renderer.triangle_data.colors[renderer.indices.triangle] = properties.color;

                u32 start = renderer.indices.triangle * 3;
                std::array<u32, 3> indices { 0, 1, 2 };
                for(int i = 0; i < indices.size(); i++) {
                    renderer.triangle_data.indices[start + i] = start + i;
                }

                renderer.indices.triangle++;
            }
            break;
        }
        case PrimitiveType::Quad: {
            if(can_add(properties.type, renderer)) {
                renderer.quad_data.positions[renderer.indices.quad] = properties.position;
                renderer.quad_data.colors[renderer.indices.quad] = properties.color;

                u32 start = renderer.indices.quad * 6;
                std::array<u32, 6> indices { 0, 1, 2, 2, 3, 0 };
                for(int i = 0; i < indices.size(); i++) {
                    renderer.quad_data.indices[start + i] = start + i;
                }

                renderer.indices.quad++;
            }
            break;
        }
        default: {
            return;
        }
    }
}

bool can_add(PrimitiveType type, const Renderer& renderer) {
    switch(type) {
        case PrimitiveType::Triangle: {
            return renderer.indices.triangle < Settings::object_count;
        }
        case PrimitiveType::Quad: {
            return renderer.indices.quad < Settings::object_count;
        }
        default: {
            return false;
        }
    }
}
