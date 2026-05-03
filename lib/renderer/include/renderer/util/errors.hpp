#ifndef RENDERER_UTIL_ERRORS_HPP
#define RENDERER_UTIL_ERRORS_HPP

#include <expected>

#include <spdlog/spdlog.h>

// std::expected error function templates ----------------------------------------------------------

struct ShaderError;

template <typename V, typename E>
V exit_on_error(std::expected<V, E>&& expected) {
    if(!expected.has_value()) {
        spdlog::error(expected.error());
        std::exit(EXIT_FAILURE);
    }

    return std::move(expected.value());
}

template <typename V>
V exit_on_error(std::expected<V, ShaderError>&& expected) {
    if(!expected.has_value()) {
        spdlog::error(expected.error().message);
        std::exit(EXIT_FAILURE);
    }

    return std::move(expected.value());
}

template <typename E>
void exit_on_error(std::expected<void, E>&& expected) {
    if(!expected.has_value()) {
        spdlog::error(expected.error());
        std::exit(EXIT_FAILURE);
    }
}

#endif
