#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <window/window.hpp>

std::expected<void, std::string> initialize_opengl(PlatformWindow* handle);

#endif
