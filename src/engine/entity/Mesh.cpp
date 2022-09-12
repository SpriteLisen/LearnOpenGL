//
// Created by SpriteLisen on 2022/9/11.
//

#include "Mesh.h"


void Mesh::setVertices(std::vector<Vertex> data) {
    this->vertices = data;
    float array[this->vertices.size() * 3];

    for (int i = 0; i < this->vertices.size(); i++) {
        Vertex vertex = this->vertices.at(i);
        array[i * 3 + 0] = vertex.getX();
        array[i * 3 + 1] = vertex.getY();
        array[i * 3 + 2] = vertex.getZ();
    }

    // 创建 GL VBO 对象存储顶点数据
    unsigned int vbo;
    glGenBuffers(1, &vbo);

    // 创建 VAO 对象来存储下面的操作, 之后每次需要执行操作时, 都使用 VAO 对象即可
    glGenVertexArrays(1, &this->verticesId);
    glBindVertexArray(this->verticesId);

    // 将顶点数据存储到 VBO 中, 并将下列操作记录到 VAO 中
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (int) sizeof(array), array, GL_STATIC_DRAW);
    glVertexAttribPointer(
            0, (int) (sizeof(array) / sizeof(array[0]) / 3),
            GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr
    );
    glEnableVertexAttribArray(0);

    glBindVertexArray(GL_NONE);
}

void Mesh::useVertices() {
    glBindVertexArray(this->verticesId);

    // 使用线框模式绘制图形, 默认为 GL_FILL
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (this->indicesId) {
        // 有顶点索引时按照顶点索引进行绘制
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indicesId);
        glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr);
    } else {
        // 无顶点索引时按照顶点数量进行绘制
        glDrawArrays(GL_TRIANGLES, 0, (int) vertices.size());
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
}

void Mesh::setIndices(std::vector<unsigned int> data) {
    this->indices = data;
    int array[this->indices.size()];

    for (int i = 0; i < this->indices.size(); i++) {
        array[i] = this->indices.at(i);
    }

    // 创建 EBO 对象用于存储顶点的绘制索引顺序
    glGenBuffers(1, &indicesId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int) sizeof(array), array, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
}