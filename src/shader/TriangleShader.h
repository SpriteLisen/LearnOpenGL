//
// Created by SpriteLisen on 2022/9/11.
//

#ifndef LEARNOPENGL_TRIANGLESHADER_H
#define LEARNOPENGL_TRIANGLESHADER_H

#include "../engine/shader/Shader.h"

class TriangleShader : public Shader {
public:
    TriangleShader(const char *vertexShaderSource, const char *fragmentShaderSource);
    static Shader create();
};


#endif //LEARNOPENGL_TRIANGLESHADER_H
