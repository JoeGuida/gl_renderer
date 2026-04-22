#ifndef RENDERER_CORE_MATERIAL_HPP
#define RENDERER_CORE_MATERIAL_HPP

#include <optional>

#include "renderer/core/texture.hpp"
#include "renderer/types/vec.hpp"

struct Material {
    vec4 color;

    std::optional<Texture> color_map;
};

#endif
