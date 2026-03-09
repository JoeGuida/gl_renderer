#ifndef RENDERER_SHADER_HPP
#define RENDERER_SHADER_HPP

#include <expected>
#include <string>
#include <variant>

#include <window/win32.hpp>

#include <renderer/file.hpp>
#include <renderer/gl_loader.hpp>
#include <renderer/shader_type.hpp>
#include <renderer/types.hpp>

struct ShaderError {
    std::string message;
};

std::expected<std::string, ShaderError> get_extension(ShaderType type);
std::expected<u32, std::variant<FileError, ShaderError>> compile_shader(const std::filesystem::path& source_folder, const std::string& name, ShaderType type);
std::expected<u32, ShaderError> link_shaders(u32 vertex, u32 fragment);
void set_shader_uniform(u32 program, const std::string& uniform, float value);
void set_shader_uniform(u32 program, const std::string& uniform, const mat4& value);
void set_shader_uniform(u32 program, const std::string& uniform, const vec3& value);

#endif

