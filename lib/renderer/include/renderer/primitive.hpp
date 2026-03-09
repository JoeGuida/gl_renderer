#ifndef RENDERER_PRIMITIVE_HPP
#define RENDERER_PRIMITIVE_HPP

#include <renderer/types.hpp>

enum class PrimitiveType : u32 {
    Line,
    LineStrip,
    Point,
    Triangle,
    TriangleStrip,
};

#endif
