#ifndef RENDERER_LOGGER_HPP
#define RENDERER_LOGGER_HPP

#include <expected>
#include <string>

std::expected<void, std::string> init_logger();

#endif
