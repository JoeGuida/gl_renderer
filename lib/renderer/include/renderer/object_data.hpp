#ifndef RENDERER_OBJECT_DATA_HPP
#define RENDERER_OBJECT_DATA_HPP

#include <array>

#include <renderer/primitive.hpp>
#include <renderer/settings.hpp>
#include <renderer/vector.hpp>
#include <renderer/vertex.hpp>

template <PrimitiveType T>
struct ObjectData {
    std::array<vec3_std140, Settings::object_count> positions;
    std::array<vec3_std140, Settings::object_count> colors;
    static constexpr std::array<Vertex, PrimitiveTraits<T>::vertex_count> vertices = PrimitiveTraits<T>::vertices;
    static constexpr std::array<u32, PrimitiveTraits<T>::index_count> indices = PrimitiveTraits<T>::indices;
};

#endif
