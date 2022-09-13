//
// Created by SpriteLisen on 2022/9/13.
//

#ifndef LEARNOPENGL_GPUACTION_H
#define LEARNOPENGL_GPUACTION_H

#include "glad/glad.h"

class GPUAction {
public:
    GPUAction();
    void use() const;
    void unbind() const;
private:
    unsigned int id;
};


#endif //LEARNOPENGL_GPUACTION_H
