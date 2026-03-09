#ifndef RENDERER_SHADER_TYPE_HPP
#define RENDERER_SHADER_TYPE_HPP

#include <renderer/glcorearb.h>

enum class ShaderType : GLenum {
    Vertex      = GL_VERTEX_SHADER,
    Fragment    = GL_FRAGMENT_SHADER,
    Geometry    = GL_GEOMETRY_SHADER,
    Compute     = GL_COMPUTE_SHADER,
    TessControl = GL_TESS_CONTROL_SHADER,
    TessEval    = GL_TESS_EVALUATION_SHADER,
    None
};

#endif
