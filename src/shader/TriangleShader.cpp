//
// Created by SpriteLisen on 2022/9/11.
//

#include "TriangleShader.h"

TriangleShader::TriangleShader(
        const char *vertexShaderSource, const char *fragmentShaderSource
)
        : Shader(vertexShaderSource, fragmentShaderSource) {

}

Shader TriangleShader::create() {
    const char *vertexShader = "#version 330 core\n"
                               "layout (location = 0) in vec4 aPos;\n"
                               "layout (location = 1) in vec4 aColors;\n"
                               "out vec4 fColors;\n\n"
                               "void main()\n"
                               "{\n"
                               "    fColors = aColors;\n"
                               "    gl_Position = aPos;\n"
                               "}\n";

    const char *fragmentShader = "#version 330 core\n"
                                 "//uniform vec4 uColor;\n"
                                 "in vec4 fColors;\n"
                                 "out vec4 FragColor;\n\n"
                                 "void main()\n"
                                 "{\n"
                                 "    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "    // FragColor = uColor;\n"
                                 "    FragColor = fColors;\n"
                                 "}\n";

    return TriangleShader(vertexShader, fragmentShader);
}