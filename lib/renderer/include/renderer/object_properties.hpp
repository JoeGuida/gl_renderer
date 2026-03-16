#ifndef RENDERER_OBJECT_PROPERTIES_HPP
#define RENDERER_OBJECT_PROPERTIES_HPP

#include <renderer/primitive.hpp>
#include <renderer/vector.hpp>

struct ObjectProperties {
    vec3 position;
    vec3 color;
    PrimitiveType type;
};

#endif
