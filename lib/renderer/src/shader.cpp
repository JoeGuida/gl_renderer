#include <renderer/shader.hpp>
#include <format>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include <renderer/convert.hpp>
#include <renderer/file.hpp>
#include <renderer/gl_loader.hpp>

std::expected<u32, ShaderError> compile(const Shader& shader) {
    std::vector<u32> compiled;
    for(auto stage : shader.stages) {
        std::filesystem::path shader_path = get_shader_path(shader.name, stage);

        auto id = compile_shader(shader_path, stage);
        if(!id.has_value()) {
            if(std::holds_alternative<ShaderError>(id.error())) {
                return std::unexpected(std::get<ShaderError>(id.error()));
            }
        }

        compiled.push_back(id.value());
    }

    auto shader_program = link_shaders(compiled);
    if(!shader_program.has_value()) {
        return std::unexpected(shader_program.error());
    }

    return shader_program.value();
}

/*
    All shaders are stored at root/shaders
    get file extension by shader stage
*/
std::filesystem::path get_shader_path(const std::string& name, ShaderStage stage) {
    std::filesystem::path shader_path = std::filesystem::current_path() / "shaders";
    switch(stage) {
        case ShaderStage::Vertex: {
            return shader_path / std::format("{}.vert", name);
        }
        case ShaderStage::Fragment: {
            return shader_path / std::format("{}.frag", name);
        }
        default: {
            return {};
        }
    }
}

std::expected<u32, std::variant<FileError, ShaderError>> compile_shader(std::filesystem::path path, ShaderStage stage) {
    std::ifstream shader_file(path);

    if(!shader_file) {
        FileError error{
            .message = std::format("FileError :: could not read file at {}", path.string())
        };
        return std::unexpected(error);
    }

    shader_file.seekg(0, std::ios::end);
    size_t size = shader_file.tellg();
    shader_file.seekg(0);
    std::string buffer(size, '\0');
    shader_file.read(&buffer[0], size);

    u32 id = glCreateShader(static_cast<GLenum>(stage));
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

std::expected<u32, ShaderError> link_shaders(const std::vector<u32> compiled) {
    u32 program = glCreateProgram();

    for(auto id : compiled) {
        glAttachShader(program, id);
    }
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		int log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

		std::string log(log_length, '\0');
		glGetProgramInfoLog(program, log_length, nullptr, log.data());

		glDeleteProgram(program);
        for(auto id : compiled) {
	        glDeleteShader(id);
        }

        ShaderError error{
            .message = std::format("ShaderError :: shader program linking failed :: {}", log)
        };
		return std::unexpected(error);
	}

    for(auto id : compiled) {
        glDetachShader(program, id);
        glDeleteShader(id);
    }

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

