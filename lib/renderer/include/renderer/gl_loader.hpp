#ifndef RENDERER_GL_LOADER_HPP
#define RENDERER_GL_LOADER_HPP

#include <Windows.h>
#include <GL/gl.h>

#include <renderer/glcorearb.h>
#include <renderer/wglext.h>

extern PFNGLATTACHSHADERPROC             glAttachShader;
extern PFNGLBINDBUFFERPROC               glBindBuffer;
extern PFNGLBINDBUFFERBASEPROC           glBindBufferBase;
extern PFNGLBUFFERDATAPROC               glBufferData;
extern PFNGLBUFFERSUBDATAPROC            glBufferSubData;
extern PFNGLBINDVERTEXARRAYPROC          glBindVertexArray;
extern PFNGLCOMPILESHADERPROC            glCompileShader;
extern PFNGLCREATEPROGRAMPROC            glCreateProgram;
extern PFNGLCREATESHADERPROC             glCreateShader;
extern PFNGLDELETEPROGRAMPROC            glDeleteProgram;
extern PFNGLDELETESHADERPROC             glDeleteShader;
extern PFNGLDETACHSHADERPROC             glDetachShader;
extern PFNGLDRAWARRAYSINSTANCEDPROC      glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC    glDrawElementsInstanced;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC               glGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays;
extern PFNGLGETBUFFERPARAMETERIVPROC     glGetBufferParameteriv;
extern PFNGLGETPROGRAMIVPROC             glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC              glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC       glGetUniformLocation;
extern PFNGLLINKPROGRAMPROC              glLinkProgram;
extern PFNGLSHADERSOURCEPROC             glShaderSource;
extern PFNGLUNIFORM3FVPROC               glUniform3fv;
extern PFNGLUNIFORM1FPROC                glUniform1f;
extern PFNGLUNIFORMMATRIX4FVPROC         glUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC               glUseProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

inline bool loaded = false;
void load_gl_functions();

#endif

