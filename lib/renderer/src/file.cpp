#include "renderer/scene/file.hpp"

#include <format>
#include <fstream>

std::expected<std::vector<std::string>, FileError> read_file(const std::filesystem::path& path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        FileError error{
            .message = std::format("FileError :: could not open file {}", path.string())
        };
        return std::unexpected(error);
    }

    std::vector<std::string> data;
    std::string str;
    while(std::getline(file, str)) {
        data.push_back(str);
    }

    return data;
}
