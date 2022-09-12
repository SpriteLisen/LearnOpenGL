//
// Created by SpriteLisen on 2022/9/11.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H

#include <vector>
#include "Vertex.h"
#include "glad/glad.h"

class Mesh {
public:
    void setVertices(std::vector<Vertex> data);
    void useVertices();

    void setIndices(std::vector<unsigned int> data);
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int verticesId;
    unsigned int indicesId;
};


#endif //LEARNOPENGL_MESH_H
