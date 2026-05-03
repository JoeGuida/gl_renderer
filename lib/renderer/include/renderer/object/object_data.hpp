#ifndef RENDERER_OBJECT_OBJECT_DATA_HPP
#define RENDERER_OBJECT_OBJECT_DATA_HPP

#include <array>

#include "renderer/settings/renderer_settings.hpp"
#include "renderer/object/primitive.hpp"
#include "renderer/types/uint.hpp"
#include "renderer/types/vec.hpp"

struct ObjectData {
    std::array<vec4, RendererSettings::total_object_count> positions;
    std::array<vec4, RendererSettings::total_object_count> scales;
    std::array<vec4, RendererSettings::total_object_count> colors;
};

#endif
