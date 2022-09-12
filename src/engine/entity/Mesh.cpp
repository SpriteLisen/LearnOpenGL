//
// Created by SpriteLisen on 2022/9/11.
//

#include "Mesh.h"

void Mesh::setVertices(std::vector<Vertex> *data, const char *attribName) {
    if (data == nullptr || attribName == nullptr) {
        throw std::runtime_error("The params must not be nullptr!");
    }

    this->vertices = data;

    float array[this->vertices->size() * 4];
    for (int i = 0; i < this->vertices->size(); i++) {
        Vertex vertex = this->vertices->at(i);
        array[i * 4 + 0] = vertex.getX();
        array[i * 4 + 1] = vertex.getY();
        array[i * 4 + 2] = vertex.getZ();
        array[i * 4 + 3] = vertex.getW();
    }
    verticesBuffer = new GPUBuffer(array, (int) sizeof(array));

    this->verticesAttribName = attribName;
}

void Mesh::bindToShader(int verticesIndex, int colorsIndex) {
    if (this->vertices == nullptr || this->verticesBuffer == nullptr) {
        return;
    }

    // Create VAO, save actions
    glGenVertexArrays(1, &this->verticesId);
    glBindVertexArray(this->verticesId);

    // use vertex buffer
    verticesBuffer->bind();
    glEnableVertexAttribArray(verticesIndex);
    glVertexAttribPointer(
            verticesIndex, (int) vertices->size(), GL_FLOAT,
            GL_FALSE, 4 * sizeof(float), (void *) nullptr
    );

    // have color, use color
    if (colorsBuffer != nullptr) {
        colorsBuffer->bind();

        glEnableVertexAttribArray(colorsIndex);
        glVertexAttribPointer(
                colorsIndex, (int) colors->size(), GL_FLOAT,
                GL_FALSE, 4 * sizeof(float), (void *) nullptr
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindVertexArray(GL_NONE);
}

void Mesh::setColors(std::vector<Color> *data, const char *attribName) {
    if (data == nullptr || attribName == nullptr) {
        throw std::runtime_error("The params must not be nullptr!");
    }

    this->colors = data;

    float array[this->colors->size() * 4];
    for (int i = 0; i < this->colors->size(); i++) {
        Color color = this->colors->at(i);
        array[i * 4 + 0] = color.getRed();
        array[i * 4 + 1] = color.getGreen();
        array[i * 4 + 2] = color.getBlue();
        array[i * 4 + 3] = color.getAlpha();
    }
    colorsBuffer = new GPUBuffer(array, (int) sizeof(array));

    this->colorsAttribName = attribName;
}

void Mesh::setIndices(std::vector<unsigned int> *data) {
    this->indices = data;
    unsigned int array[this->indices->size()];

    for (int i = 0; i < this->indices->size(); i++) {
        array[i] = this->indices->at(i);
    }

    indicesBuffer = new GPUBuffer(array, (int) sizeof(array), STATIC, ELEMENT_ARRAY);
}

void Mesh::use() {
    // Must have vertices
    if (this->verticesId == -1) {
        return;
    }
    glBindVertexArray(this->verticesId);

    // 使用线框模式绘制图形, 默认为 GL_FILL
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (indicesBuffer != nullptr) {
        // 有顶点索引时按照顶点索引进行绘制
        indicesBuffer->bind();
        glDrawElements(GL_TRIANGLES, (int) indices->size(), GL_UNSIGNED_INT, nullptr);
    } else {
        // 无顶点索引时按照顶点数量进行绘制
        glDrawArrays(GL_TRIANGLES, 0, (int) vertices->size());
    }

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
}