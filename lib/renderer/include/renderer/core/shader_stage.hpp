#ifndef RENDERER_CORE_SHADER_STAGE_HPP
#define RENDERER_CORE_SHADER_STAGE_HPP

#include "renderer/gl/glcorearb.h"

enum class ShaderStage : GLenum {
    Vertex      = GL_VERTEX_SHADER,
    Fragment    = GL_FRAGMENT_SHADER,
    Geometry    = GL_GEOMETRY_SHADER,
    Compute     = GL_COMPUTE_SHADER,
    TessControl = GL_TESS_CONTROL_SHADER,
    TessEval    = GL_TESS_EVALUATION_SHADER,
    None
};

#endif
