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
                               "layout (location = 0) in vec3 aPos;\n\n"
                               "void main()\n"
                               "{\n"
                               "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                               "}\n";

    const char *fragmentShader = "#version 330 core\n"
                                 "uniform vec4 uColor;\n"
                                 "out vec4 FragColor;\n\n"
                                 "void main()\n"
                                 "{\n"
                                 "    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "    FragColor = uColor;\n"
                                 "}\n";

    return TriangleShader(vertexShader, fragmentShader);
}