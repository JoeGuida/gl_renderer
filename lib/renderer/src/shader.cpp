#include <renderer/shader.hpp>

#include <format>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include <renderer/convert.hpp>
#include <renderer/file.hpp>
#include <renderer/gl_loader.hpp>

std::expected<std::string, ShaderError> get_extension(ShaderType type) {
    switch(type) {
        case ShaderType::Vertex: {
            return ".vert";
        }
        case ShaderType::Fragment: {
            return ".frag";
        }
        default: {
            ShaderError error{
                .message = std::format("ShaderError :: Invalid Shader Type {}", Convert::to_string(type))
            };
            return std::unexpected(error);
        }
    }
}

std::expected<u32, std::variant<FileError, ShaderError>> compile_shader(const std::filesystem::path& source_folder, const std::string& name, ShaderType type) {
    auto extension = get_extension(type);
    if(!extension.has_value()) {
        return std::unexpected(extension.error());
    }

    std::string shader_filename = name + extension.value();
    std::filesystem::path filepath = source_folder / shader_filename;
    std::ifstream shader_file(filepath);
    if(!shader_file) {
        FileError error{
            .message = std::format("FileError :: could not read file at {}", filepath.string())
        };
        return std::unexpected(error);
    }

    shader_file.seekg(0, std::ios::end);
    size_t size = shader_file.tellg();
    shader_file.seekg(0);
    std::string buffer(size, '\0');
    shader_file.read(&buffer[0], size);

    u32 id = glCreateShader(static_cast<GLenum>(type));
    const char* s = buffer.data();
	glShaderSource(id, 1, &s, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		int log_length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
		std::string log(log_length, ' ');
		glGetShaderInfoLog(id, log_length, nullptr, &log[0]);

		glDeleteShader(id);
        ShaderError error{
            .message = std::format("ShaderError :: shader compilation failed :: {}", log)
        };
		return std::unexpected(error);
	}

	return id;
}

std::expected<u32, ShaderError> link_shaders(u32 vertex, u32 fragment) {
    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		int log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length, '\0');
		glGetProgramInfoLog(program, log_length, nullptr, log.data());

		glDeleteProgram(program);
	    glDeleteShader(vertex);
	    glDeleteShader(fragment);

        ShaderError error{
            .message = std::format("ShaderError :: shader program linking failed :: {}", log)
        };
		return std::unexpected(error);
	}

	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

void set_shader_uniform(u32 program, const std::string& uniform, float value) {
    glUniform1f(glGetUniformLocation(program, uniform.c_str()), value);
}

void set_shader_uniform(u32 program, const std::string& uniform, const mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(program, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void set_shader_uniform(u32 program, const std::string& uniform, const vec3& value) {
    glUniform3fv(glGetUniformLocation(program, uniform.c_str()), 1, glm::value_ptr(value));
}

