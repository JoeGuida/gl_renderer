#ifndef RENDERER_CONVERT_HPP
#define RENDERER_CONVERT_HPP

#include <string>

#include <renderer/shader_stage.hpp>
#include <renderer/vector.hpp>

struct Convert {
    static std::string to_string(ShaderStage stage);
    static vec4 to_vec4(const vec3& v);
};

#endif
