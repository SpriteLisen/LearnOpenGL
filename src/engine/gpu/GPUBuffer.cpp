//
// Created by SpriteLisen on 2022/9/12.
//

#include "GPUBuffer.h"

GPUBuffer::GPUBuffer(
        const void *data, int dataSize,
        DataType dataType, BufferType bufferType
) {
    id = -1;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);

    // Init drawType
    GLenum drawType;
    switch (dataType) {
        case STATIC:
            drawType = GL_STATIC_DRAW;
            break;
        case DYNAMIC:
            drawType = GL_DYNAMIC_DRAW;
            break;
        case STREAM:
            drawType = GL_STREAM_DRAW;
            break;
        default:
            drawType = GL_STATIC_DRAW;
            break;
    }

    // Init arrayType
    switch (bufferType) {
        case ARRAY:
            arrayType = GL_ARRAY_BUFFER;
            break;
        case ELEMENT_ARRAY:
            arrayType = GL_ELEMENT_ARRAY_BUFFER;
            break;

    }

    glBufferData(GL_ARRAY_BUFFER, dataSize, data, drawType);

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
}

void GPUBuffer::bind() const {
    glBindBuffer(arrayType, id);
}

