#version 330 core
//uniform vec4 uColor;
in vec4 fColors;
out vec4 FragColor;

void main() {
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n
    // FragColor = uColor;\n
    FragColor = fColors;
}