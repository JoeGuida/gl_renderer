#ifndef RENDERER_UTIL_CONVERT_HPP
#define RENDERER_UTIL_CONVERT_HPP

#include <string>

#include "renderer/core/shader_stage.hpp"
#include "renderer/types/vec.hpp"

struct Convert {
    static std::string to_string(ShaderStage stage);
    static vec4 to_vec4(const vec3& v);
};

#endif
