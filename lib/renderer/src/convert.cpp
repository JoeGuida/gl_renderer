#include <renderer/convert.hpp>

std::string Convert::to_string(ShaderStage stage) {
    switch(stage) {
        case ShaderStage::Vertex: {
            return "Vertex";
        }
        case ShaderStage::Fragment: {
            return "Fragment";
        }
        default: {
            return "None";
        }
    }
}

vec4 Convert::to_vec4(const vec3& v) {
    return vec4(v.x, v.y, v.z, 1.0f);
}
