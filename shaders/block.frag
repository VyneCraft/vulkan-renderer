#version 460 core

layout (location = 0) in vec4 vertex_color;

layout (location = 0) out vec4 pixel_color;

void main() {
    pixel_color = vertex_color;
}
