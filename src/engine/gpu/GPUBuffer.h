//
// Created by SpriteLisen on 2022/9/12.
//

#ifndef LEARNOPENGL_GPUBUFFER_H
#define LEARNOPENGL_GPUBUFFER_H

#include "glad/glad.h"

enum DataType {
    STATIC, DYNAMIC, STREAM
};

enum BufferType {
    ARRAY, ELEMENT_ARRAY
};

class GPUBuffer {
public:
    GPUBuffer(const void *data, int dataSize, DataType dataType = STATIC, BufferType bufferType = ARRAY);

    void bind() const;

private:
    GLenum arrayType;
    unsigned int id;
};


#endif //LEARNOPENGL_GPUBUFFER_H
