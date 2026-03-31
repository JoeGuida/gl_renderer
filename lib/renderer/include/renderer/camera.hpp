#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <renderer/transform.hpp>
#include <renderer/vector.hpp>

struct Camera {
    Transform transform;
    vec3 direction;
    float aspect;
    float fov;
    float near;
    float far;
};

#endif
