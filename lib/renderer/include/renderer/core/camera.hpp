#ifndef RENDERER_CORE_CAMERA_HPP
#define RENDERER_CORE_CAMERA_HPP

#include "renderer/core/transform.hpp"
#include "renderer/types/float.hpp"
#include "renderer/types/vec.hpp"

struct Camera {
    Transform transform;
    vec3 direction;
    f32 aspect;
    f32 fov;
    f32 near;
    f32 far;
};

#endif
