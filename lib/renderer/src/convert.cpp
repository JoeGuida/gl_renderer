#include <renderer/convert.hpp>

std::string Convert::to_string(ShaderType type) {
    switch(type) {
        case ShaderType::Vertex: {
            return "Vertex";
        }
        case ShaderType::Fragment: {
            return "Fragment";
        }
        default: {
            return "None";
        }
    }
}
