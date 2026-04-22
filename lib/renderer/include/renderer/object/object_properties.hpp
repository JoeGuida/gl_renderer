#ifndef RENDERER_OBJECT_OBJECT_PROPERTIES_HPP
#define RENDERER_OBJECT_OBJECT_PROPERTIES_HPP

#include "renderer/core/material.hpp"
#include "renderer/types/vec.hpp"

struct ObjectProperties {
    vec3 position;
    Material material;
};

#endif
