#include <renderer/renderer.hpp>

#include <array>

#include <window/win32.hpp>

#include <renderer/gl_loader.hpp>
#include <renderer/primitive.hpp>
#include <renderer/vector.hpp>
#include <renderer/wglext.h>

void add_primitive(PrimitiveType type, const ObjectProperties& properties, Renderer& renderer) {
    if(type == PrimitiveType::Triangle && renderer.count.triangle < Settings::object_count) {
        u32 index = Triangle::offset + renderer.count.triangle;
        renderer.object_data.positions[index] = vec4(properties.position, 1.0f);
        renderer.object_data.colors[index] = vec4(properties.color, 1.0);
        ++renderer.count.triangle;
        upload_ubo(renderer);
    }

    if(type == PrimitiveType::Quad && renderer.count.quad < Settings::object_count) {
        u32 index = Quad::offset + renderer.count.quad;
        renderer.object_data.positions[index] = vec4(properties.position, 1.0f);
        renderer.object_data.colors[index] = vec4(properties.color, 1.0f);
        ++renderer.count.quad;
        upload_ubo(renderer);
    }
}

void draw(Renderer& renderer, u32 shader) {
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(renderer.vao);
    glUseProgram(shader);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, renderer.count.triangle);
    glDrawElementsInstanced(GL_TRIANGLES, Quad::indices.size(), GL_UNSIGNED_INT, Quad::indices.data(), renderer.count.quad);
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

    std::array<int, 7> attribs = {
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

    HGLRC hglrc = wglCreateContextAttribsARB(handle->hdc, nullptr, attribs.data());
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

std::expected<void, std::string> initialize_renderer(Renderer& renderer) {
    auto opengl = initialize_opengl(renderer.window_handle);
    if(!opengl.has_value()) {
        return std::unexpected(opengl.error());
    }

    glGenVertexArrays(1, &renderer.vao);
    glGenBuffers(1, &renderer.vbo);
    glGenBuffers(1, &renderer.ubo);

    glBindVertexArray(renderer.vao);
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubo);
    glBufferData(GL_UNIFORM_BUFFER, Settings::buffer_size * Settings::buffer_count, nullptr, GL_DYNAMIC_DRAW);

    return {};
}

void setup_draw(Renderer& renderer) {
    glBindVertexArray(renderer.vao);

    glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
    glBufferData(GL_ARRAY_BUFFER, Triangle::vertex_count * sizeof(Vertex), Triangle::vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    upload_ubo(renderer);
}

void upload_ubo(Renderer& renderer) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, Settings::buffer_size, renderer.object_data.positions.data());
    glBufferSubData(GL_UNIFORM_BUFFER, Settings::buffer_size, Settings::buffer_size, renderer.object_data.colors.data());
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, renderer.ubo);
}
