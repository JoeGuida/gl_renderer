#ifndef WINDOW_WIN32_WINDOW_HPP
#define WINDOW_WIN32_WINDOW_HPP

#include <expected>
#include <functional>
#include <memory>
#include <string>

#include "win32.hpp"

struct PlatformWindow {
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
};

std::pair<uint32_t, uint32_t> get_window_size(PlatformWindow* window);
void run_window(PlatformWindow* handle, std::function<void()> draw);
LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
std::expected<std::unique_ptr<PlatformWindow>, std::string> initialize_window(HINSTANCE instance, int show_window_flags, uint32_t width, uint32_t height, const wchar_t* class_name, const wchar_t* window_title);

#endif
