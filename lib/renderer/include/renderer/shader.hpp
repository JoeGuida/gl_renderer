#ifndef RENDERER_SHADER_HPP
#define RENDERER_SHADER_HPP

#include <expected>
#include <string>
#include <variant>

#include <window/win32.hpp>

#include <renderer/file.hpp>
#include <renderer/gl_loader.hpp>
#include <renderer/matrix.hpp>
#include <renderer/shader_stage.hpp>
#include <renderer/uint.hpp>
#include <renderer/vector.hpp>

struct ShaderError {
    std::string message;
};

struct Shader {
    std::string name;
    std::vector<ShaderStage> stages;
};

std::expected<u32, ShaderError> compile(const Shader& shader);
std::filesystem::path get_shader_path(const std::string& name, ShaderStage stage);
std::expected<u32, std::variant<FileError, ShaderError>> compile_shader(std::filesystem::path path, ShaderStage stage);
std::expected<u32, ShaderError> link_shaders(const std::vector<u32> compiled);
void set_shader_uniform(u32 program, const std::string& uniform, float value);
void set_shader_uniform(u32 program, const std::string& uniform, const mat4& value);
void set_shader_uniform(u32 program, const std::string& uniform, const vec3& value);

#endif

