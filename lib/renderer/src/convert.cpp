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
