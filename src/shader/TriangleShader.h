//
// Created by SpriteLisen on 2022/9/11.
//

#ifndef LEARNOPENGL_TRIANGLESHADER_H
#define LEARNOPENGL_TRIANGLESHADER_H

#include <string>
#include "../engine/shader/Shader.h"

class TriangleShader : public Shader {
public:
    static Shader create();

private:
    TriangleShader(const std::string &vertexSourceFilePath, const std::string &fragmentSourceFilePath);
};

#endif //LEARNOPENGL_TRIANGLESHADER_H
