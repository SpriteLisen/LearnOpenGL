//
// Created by SpriteLisen on 2022/9/11.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H

#include <vector>
#include <iostream>
#include "Entity.h"
#include "../gpu/GPUAction.h"
#include "../gpu/GPUBuffer.h"
#include "glad/glad.h"

class Mesh {
public:
    std::vector<Vertex> *vertices = nullptr;
    const char *verticesAttribName = nullptr;
    void setVertices(std::vector<Vertex> *data, const char* attribName);
    void bindToShader(int verticesIndex, int colorsIndex);

    std::vector<Color> *colors = nullptr;
    const char *colorsAttribName = nullptr;
    void setColors(std::vector<Color> *data, const char* attribName);

    std::vector<unsigned int> *indices = nullptr;
    void setIndices(std::vector<unsigned int> *data);

    void use();
private:
    GPUAction *action = nullptr;
    GPUBuffer *verticesBuffer = nullptr;
    GPUBuffer *colorsBuffer = nullptr;
    GPUBuffer *indicesBuffer = nullptr;
};


#endif //LEARNOPENGL_MESH_H
