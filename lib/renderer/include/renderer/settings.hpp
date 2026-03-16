#ifndef RENDERER_SETTINGS_HPP
#define RENDERER_SETTINGS_HPP

#include <renderer/vector.hpp>
#include <renderer/uint.hpp>

struct Settings {
    static constexpr u32 object_count = 256;
    static constexpr u32 max_vertex_count_per_primitive = 4;
    static constexpr u32 max_index_count_per_primitive = 6;
    static constexpr u32 index_count = max_index_count_per_primitive * object_count;
    static constexpr u32 buffer_size = sizeof(vec3_std140) * object_count;
    static constexpr u32 buffer_count = 4;
};

#endif
