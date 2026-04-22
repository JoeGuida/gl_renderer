#ifndef RENDERER_CORE_SHADER_HPP
#define RENDERER_CORE_SHADER_HPP

#include <expected>
#include <filesystem>
#include <string>
#include <variant>

#include <window/win32.hpp>

#include "renderer/api/gl_loader.hpp"
#include "renderer/core/shader_stage.hpp"
#include "renderer/scene/file.hpp"
#include "renderer/types/float.hpp"
#include "renderer/types/matrix.hpp"
#include "renderer/types/uint.hpp"
#include "renderer/types/vec.hpp"

struct ShaderError {
    std::string message;
};

struct Shader {
    std::string name;
    std::vector<ShaderStage> stages;
};

std::expected<u32, ShaderError> compile(const Shader& shader);
std::expected<u32, ShaderError> compile(const Shader& shader, std::filesystem::path root_path);
std::filesystem::path get_shader_path(const std::string& name, ShaderStage stage);
std::filesystem::path get_shader_path(const std::string& name, ShaderStage stage, std::filesystem::path root_path);
std::expected<u32, std::variant<FileError, ShaderError>> compile_shader(std::filesystem::path path, ShaderStage stage);
std::expected<u32, ShaderError> link_shaders(const std::vector<u32> compiled);
void set_shader_uniform(u32 program, const std::string& uniform, u32 value);
void set_shader_uniform(u32 program, const std::string& uniform, f32 value);
void set_shader_uniform(u32 program, const std::string& uniform, const mat4& value);
void set_shader_uniform(u32 program, const std::string& uniform, const vec3& value);

#endif

