#ifndef RENDERER_VECTOR_HPP
#define RENDERER_VECTOR_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

struct alignas(16) vec2_std140 {
    glm::vec2 v;

    operator glm::vec2&() { return v; }
    operator const glm::vec2&() const { return v; }

    vec2_std140() = default;
    vec2_std140(const glm::vec2& v) : v(v) {}
};

struct alignas(16) vec3_std140 {
    glm::vec3 v;

    operator glm::vec3&() { return v; }
    operator const glm::vec3&() const { return v; }

    vec3_std140() = default;
    vec3_std140(const glm::vec3& v) : v(v) {}
};

#endif
