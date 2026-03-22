#version 460 core

const uint N = 64;

layout (location = 0) in vec3 pos;

layout (std140, binding = 0) uniform vertex_data {
    vec4 positions[N];
    vec4 colors[N];
};

out vec4 vertex_color;

void main() {
    gl_Position = vec4(pos, 0.0) + positions[gl_InstanceID]; // positions[i].w will always be 1
    vertex_color = colors[gl_InstanceID];
}
