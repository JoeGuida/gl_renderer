#version 460 core

const uint N = 256;

layout (std140, binding = 0) uniform vertex_data {
    vec3 positions[N];
    vec3 colors[N];
};

out vec3 vertex_color;

void main() {
    gl_Position = vec4(positions[gl_VertexID], 1.0);
    vertex_color = colors[gl_VertexID];
}
