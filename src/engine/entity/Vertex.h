//
// Created by SpriteLisen on 2022/9/10.
//

#ifndef LEARNOPENGL_VERTEX_H
#define LEARNOPENGL_VERTEX_H


class Vertex {
public:
    Vertex(float x, float y, float z, float w=1.0f);
    float getX();
    float getY();
    float getZ();
    float getW();
private:
    float x, y, z, w;
};


#endif //LEARNOPENGL_VERTEX_H
