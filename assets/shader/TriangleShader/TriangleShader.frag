#version 330 core
//uniform vec4 uColor;
in vec4 fColors;
in vec2 fTexCoords;
out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n
    // FragColor = uColor;\n
    // FragColor = fColors;
    // FragColor = texture(tex1, fTexCoords);
    FragColor = mix(texture(tex1, fTexCoords), texture(tex2, fTexCoords), 0.5);
}