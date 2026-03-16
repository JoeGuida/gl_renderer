#ifndef RENDERER_MATRIX_HPP
#define RENDERER_MATRIX_HPP

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;

struct alignas(16) mat3_std140 {
    glm::mat3 m;

    operator glm::mat3&() { return m; }
    operator const glm::mat3&() const { return m; }

    mat3_std140() = default;
    mat3_std140(const glm::mat4& m) : m(m) {}
};

#endif
