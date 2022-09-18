#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColors;
layout (location = 2) in vec2 aTexCoords;

out vec4 fColors;
out vec2 fTexCoords;

uniform mat4 matrix;

void main() {
    fColors = aColors;
    fTexCoords = aTexCoords;
    gl_Position = matrix * aPos;
}