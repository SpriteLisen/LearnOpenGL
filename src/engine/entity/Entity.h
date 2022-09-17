//
// Created by SpriteLisen on 2022/9/17.
//

#ifndef LEARNOPENGL_ENTITY_H
#define LEARNOPENGL_ENTITY_H

class Vertex {
public:
    Vertex(float x, float y, float z, float w = 1.0f) : _x(x), _y(y), _z(z), _w(w) {

    }

    float x() {
        return _x;
    }

    float y() {
        return _y;
    }

    float z() {
        return _z;
    }

    float w() {
        return _w;
    }

private:
    float _x, _y, _z, _w;
};

class Color {
public:
    Color(float r, float g, float b, float a = 1.0f) : _r(r), _g(g), _b(b), _a(a) {

    }

    float r() {
        return _r;
    }

    float g() {
        return _g;
    }

    float b() {
        return _b;
    }

    float a() {
        return _a;
    }

private:
    float _r, _g, _b, _a;
};

class UV {
public:
    UV(float s, float t) : _s(s), _t(t) {

    }

    float s() {
        return _s;
    }

    float t() {
        return _t;
    }

private:
    float _s, _t;
};


#endif //LEARNOPENGL_ENTITY_H
