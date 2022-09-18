//
// Created by SpriteLisen on 2022/9/12.
//

#include "GPUBuffer.h"

GPUBuffer::GPUBuffer(
        const void *data, int dataSize,
        DataType dataType, BufferType bufferType
) {
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

    glGenBuffers(1, &id);
    glBindBuffer(arrayType, id);

    glBufferData(arrayType, dataSize, data, drawType);

    glBindBuffer(arrayType, GL_NONE);
}

void GPUBuffer::bind() const {
    glBindBuffer(arrayType, id);
}

void GPUBuffer::unbind() const {
    glBindBuffer(arrayType, GL_NONE);
}

