//
// Created by SpriteLisen on 2022/9/11.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../entity/Entity.h"
#include "../entity/Mesh.h"

class Shader {
public:
    Shader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath);
    Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
    void use();
    Shader setUniformVertex(const char *uniformName, Vertex vertex);
    Shader setUniformColor(const char *uniformName, Color color);
    Shader setUniformFloat(const char *uniformName, float value);
    Shader setUniformInt(const char *uniformName, int value);
    Shader setMat4(const char *uniformName, glm::mat4 value);

    Shader setTextures(std::vector<Texture> *textures);

    Shader bindMesh(Mesh *m);

    Shader enableDepthTest();
    Shader disableDepthTest();
private:
    void init(const char *vShaderSource, const char *fShaderSource);
    Mesh *mesh = nullptr;

    std::map<const char *, int> uniformCache;
    int getUniformIndex(const char *uniformName);
    void setUniform4f(const char *uniformName, float f1, float f2, float f3, float f4);

    std::map<const char *, int> attribCache;
    int getAttribIndex(const char *attribName);

    const char *vertexShaderSource;
    const char *fragmentShaderSource;
    unsigned int programId{};
    void compileShader();

    std::vector<Texture> *_textures = nullptr;
};


#endif //LEARNOPENGL_SHADER_H
