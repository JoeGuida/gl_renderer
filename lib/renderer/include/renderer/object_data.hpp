#ifndef RENDERER_OBJECT_DATA_HPP
#define RENDERER_OBJECT_DATA_HPP

#include <array>

#include <renderer/primitive.hpp>
#include <renderer/settings.hpp>
#include <renderer/uint.hpp>
#include <renderer/vector.hpp>

struct ObjectData {
    std::array<vec4, Settings::total_object_count> positions;
    std::array<vec4, Settings::total_object_count> colors;
};

#endif
