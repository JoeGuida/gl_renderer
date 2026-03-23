#ifndef RENDERER_SETTINGS_HPP
#define RENDERER_SETTINGS_HPP

#include <renderer/vector.hpp>
#include <renderer/uint.hpp>

struct Settings {
    static constexpr u32 primitive_count = 3;
    static constexpr u32 object_count = 64;
    static constexpr u32 buffer_size = object_count * sizeof(vec4);
    static constexpr u32 buffer_count = 2; // number of vec4 components in ObjectData
    static constexpr u32 total_object_count = object_count * primitive_count;
};

#endif
