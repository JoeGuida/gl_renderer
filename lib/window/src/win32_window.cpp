#include <window/win32_window.hpp>

#include <functional>

std::pair<uint32_t, uint32_t> get_window_size(PlatformWindow* window) {
    RECT client_rect;
    GetClientRect(window->hwnd, &client_rect);
    uint32_t width = static_cast<uint32_t>(client_rect.right - client_rect.left);
    uint32_t height = static_cast<uint32_t>(client_rect.bottom - client_rect.top);

    return { width, height };
}

void run_window(PlatformWindow* handle, std::function<void()> draw) {
    MSG message;
    ZeroMemory(&message, sizeof(MSG));
    while (true) {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT) {
                break;
            }

            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        draw();
    }
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
        case WM_CREATE: {
            return 0;
        }
        case WM_INPUT: {
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, message, wparam, lparam);
}

std::expected<std::unique_ptr<PlatformWindow>, std::string> initialize_window(HINSTANCE instance, int show_window_flags, uint32_t width, uint32_t height, const wchar_t* class_name, const wchar_t* window_title) {
    WNDCLASSEX window_class {
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = window_proc,
        .cbClsExtra = NULL,
        .cbWndExtra = NULL,
        .hInstance = instance,
        .hIcon = LoadIcon(NULL, IDI_APPLICATION),
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = nullptr,
        .lpszMenuName = NULL,
        .lpszClassName = class_name,
        .hIconSm = LoadIcon(NULL, IDI_APPLICATION)
    };

    if (!RegisterClassEx(&window_class)) {
        return std::unexpected("error registering window class");
    }

    HWND hwnd = CreateWindowEx(NULL, class_name, window_title, WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                                 NULL, NULL, instance, nullptr);

    if (!hwnd) {
        return std::unexpected("error creating window! :: hwnd is null");
    }

    HDC hdc = GetDC(hwnd);
    if(!hdc) {
        return std::unexpected("error creating window! :: hdc is null");
    }

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

    int pixel_format = ChoosePixelFormat(hdc, &pfd);
    if(!pixel_format) {
        return std::unexpected("error choosing pixel format!");
    }
    if(!SetPixelFormat(hdc, pixel_format, &pfd)) {
        return std::unexpected("error setting pixel format!");
    }

    HGLRC hglrc = wglCreateContext(hdc);
    if(!hglrc) {
        return std::unexpected("error creating gl context");
    }

    if(!wglMakeCurrent(hdc, hglrc)) {
        return std::unexpected("failed to make gl context current");
    }

    ShowWindow(hwnd, show_window_flags);
    UpdateWindow(hwnd);

    std::unique_ptr<PlatformWindow> handle = std::make_unique<PlatformWindow>();
    handle->hwnd = hwnd;
    handle->hdc = hdc;
    handle->hglrc = hglrc;

    return handle;
}
