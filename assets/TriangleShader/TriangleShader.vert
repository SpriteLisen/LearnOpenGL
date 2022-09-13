#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColors;

out vec4 fColors;

void main() {
    fColors = aColors;
    gl_Position = aPos;
}