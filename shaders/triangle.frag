#version 460 core

const uint N = 256;

layout (std140, binding = 0) uniform vertex_data {
    vec3 positions[N];
    vec3 colors[N];
};

in vec3 vertex_color;

layout (location = 0) out vec4 color;

void main() {
   color = vec4(vertex_color, 1.0);
}
