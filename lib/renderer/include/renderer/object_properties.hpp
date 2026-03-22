#ifndef RENDERER_OBJECT_PROPERTIES_HPP
#define RENDERER_OBJECT_PROPERTIES_HPP

#include <renderer/material.hpp>
#include <renderer/vector.hpp>

struct ObjectProperties {
    vec3 position;
    Material material;
};

#endif
