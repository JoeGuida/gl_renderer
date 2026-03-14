#ifndef RENDERER_TYPES_HPP
#define RENDERER_TYPES_HPP

#include <cstdint>

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

// std140 vector types
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

typedef glm::vec4 vec4;

#endif
