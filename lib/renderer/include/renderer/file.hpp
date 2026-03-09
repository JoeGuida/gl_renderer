#ifndef RENDERER_FILE_HPP
#define RENDERER_FILE_HPP

#include <expected>
#include <filesystem>
#include <string>
#include <vector>

struct FileError {
    std::string message;
};

std::expected<std::vector<std::string>, FileError> read_file(const std::filesystem::path& path);

#endif
