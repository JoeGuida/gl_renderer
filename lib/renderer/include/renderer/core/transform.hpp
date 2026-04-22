#ifndef RENDERER_CORE_TRANSFORM_HPP
#define RENDERER_CORE_TRANSFORM_HPP

#include "renderer/types/vec.hpp"

struct Transform {
    vec3 position;
    vec3 rotation;
    vec3 scale;

    static const Transform Empty;
};

void transform(Transform& transform);
void rotate(Transform& transform);
void scale(Transform& transform);

#endif
