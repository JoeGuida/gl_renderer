#ifndef RENDERER_CONVERT_HPP
#define RENDERER_CONVERT_HPP

#include <string>

#include <renderer/shader_type.hpp>

struct Convert {
    static std::string to_string(ShaderType type);
};

#endif
