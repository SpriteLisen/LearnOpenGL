//
// Created by SpriteLisen on 2022/9/11.
//

#include "TriangleShader.h"

TriangleShader::TriangleShader(const std::string &vertexSourceFilePath, const std::string &fragmentSourceFilePath)
        : Shader(vertexSourceFilePath, fragmentSourceFilePath) {

}

Shader TriangleShader::create() {
    return TriangleShader(
            "assets/TriangleShader/TriangleShader.vert",
            "assets/TriangleShader/TriangleShader.frag"
    );
}