//
// Created by SpriteLisen on 2022/9/13.
//

#include "GPUAction.h"

GPUAction::GPUAction() {
    unsigned int vaoId;
    glGenVertexArrays(1, &vaoId);
    id = vaoId;
}

void GPUAction::use() const {
    glBindVertexArray(id);
}

void GPUAction::unbind() const {
    glBindVertexArray(GL_NONE);
}

