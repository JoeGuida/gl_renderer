#ifndef RENDERER_CORE_LOGGER_HPP
#define RENDERER_CORE_LOGGER_HPP

#include <expected>
#include <string>

std::expected<void, std::string> init_logger();

#endif
