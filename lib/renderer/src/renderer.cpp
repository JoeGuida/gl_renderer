#include <renderer/renderer.hpp>

#include <window/win32.hpp>

#include <renderer/gl_loader.hpp>
#include <renderer/wglext.h>

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
