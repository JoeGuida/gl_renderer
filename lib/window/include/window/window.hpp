#ifndef WINDOW_WINDOW_HPP
#define WINDOW_WINDOW_HPP

#include <cstdint>
#include <memory>

#include "win32_window.hpp"

struct PlatformWindow;

struct Window {
    uint32_t width;
    uint32_t height;
    std::unique_ptr<PlatformWindow> handle;
};


#endif
