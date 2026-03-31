#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP

#include <optional>

#include <renderer/texture.hpp>
#include <renderer/vector.hpp>

struct Material {
    vec4 color;

    std::optional<Texture> color_map;
};

#endif
