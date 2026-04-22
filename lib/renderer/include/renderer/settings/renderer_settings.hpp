#ifndef RENDERER_SETTINGS_RENDERER_SETTINGS_HPP
#define RENDERER_SETTINGS_RENDERER_SETTINGS_HPP

#include "renderer/types/uint.hpp"
#include "renderer/types/vec.hpp"

struct RendererSettings {
    static constexpr u32 primitive_count = 3;
    static constexpr u32 object_count = 64;
    static constexpr u32 buffer_size = object_count * sizeof(vec4);
    static constexpr u32 buffer_count = 2; // number of vec4 components in ObjectData
    static constexpr u32 total_object_count = object_count * primitive_count;
};

struct SceneSettings {
    u32 width;
    u32 height;
};

#endif
