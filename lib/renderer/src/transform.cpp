#include <renderer/transform.hpp>

void transform(Transform& transform) {

}

void rotate(Transform& transform) {

}

void scale(Transform& transform) {

}

const Transform Transform::Empty = {
    .position = vec3(0.0f, 0.0f, 0.0f),
    .rotation = vec3(0.0f, 0.0f, 0.0f),
    .scale = vec3(1.0f, 1.0f, 1.0f)
};
