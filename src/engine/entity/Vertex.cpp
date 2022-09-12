//
// Created by SpriteLisen on 2022/9/10.
//

#include "Vertex.h"

Vertex::Vertex(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float Vertex::getX() {
    return this->x;
}

float Vertex::getY() {
    return this->y;
}

float Vertex::getZ() {
    return this->z;
}

float Vertex::getW() {
    return this->w;
}