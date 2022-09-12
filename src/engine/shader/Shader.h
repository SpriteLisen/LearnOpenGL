//
// Created by SpriteLisen on 2022/9/11.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <map>
#include "../entity/Vertex.h"
#include "../entity/Color.h"

class Shader {
public:
    Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
    void use() const;
    Shader setUniformVertex(const char *uniformName, Vertex vertex);
    Shader setUniformColor(const char *uniformName, Color color);
    Shader setUniformFloat(const char *uniformName, float value);
    Shader setUniformInt(const char *uniformName, int value);
private:
    std::map<const char *, int> uniformCache;
    int getUniformIndex(const char *uniformName);
    void setUniform4f(const char *uniformName, float f1, float f2, float f3, float f4);

    const char *vertexShaderSource;
    const char *fragmentShaderSource;
    unsigned int programId{};
    void compileShader();
};


#endif //LEARNOPENGL_SHADER_H
