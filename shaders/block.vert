#version 460 core

vec2 vertex_positions[3] = vec2[](
    vec2(-0.25, 0.25),
    vec2(0, -0.5),
    vec2(0.25, 0.25)
);

vec4 vertex_colors[3] = vec4[](
    vec4(1, 0, 0, 0.5),
    vec4(0, 1, 0, 1),
    vec4(0, 0, 1, 0)
);

layout (location = 0) out vec4 vertex_color;

void main() {
    gl_Position = vec4(vertex_positions[gl_VertexIndex], 0, 1);
    vertex_color = vertex_colors[gl_VertexIndex];
}
