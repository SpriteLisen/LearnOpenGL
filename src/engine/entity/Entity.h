//
// Created by SpriteLisen on 2022/9/17.
//

#ifndef LEARNOPENGL_ENTITY_H
#define LEARNOPENGL_ENTITY_H

#include "stb/stb_image.h"
#include "glad/glad.h"

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

enum TextureType {
    TEXTURE_2D
};

enum TextureWrapType {
    REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER
};

enum TextureFilterType {
    NEAREST, LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR
};

class Texture {
public:
    static Texture fromFile(
            const char *filePath,
            const char *name,
            TextureType type = TEXTURE_2D,
            TextureWrapType wrapType = REPEAT,
            TextureFilterType filterType = LINEAR
    ) {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
        return {name, data, width, height, nrChannels, type, wrapType, filterType};
    }

    const char *name() {
        return _name;
    }

    void use() const {
        glActiveTexture(GL_TEXTURE0 + _textureId - 1);
        glBindTexture(_glType, _textureId);
    }

    unsigned int id() const {
        return _textureId - 1;
    }

private:
    Texture(
            const char *name,
            unsigned char *imgData, int width, int height, int channels,
            TextureType type, TextureWrapType wrapTyp, TextureFilterType filterType
    )
            : _name(name), _imgData(imgData),
              _width(width), _height(height), _channels(channels) {

        // create a texture
        unsigned int id;
        glGenTextures(1, &id);
        _textureId = id;

        // init glType
        switch (type) {
            case TEXTURE_2D:
                _glType = GL_TEXTURE_2D;
                break;
        }
        // init glWrapType
        switch (wrapTyp) {
            case REPEAT:
                _glWrapType = GL_REPEAT;
                break;
            case MIRRORED_REPEAT:
                _glWrapType = GL_MIRRORED_REPEAT;
                break;
            case CLAMP_TO_EDGE:
                _glWrapType = GL_CLAMP_TO_EDGE;
                break;
            case CLAMP_TO_BORDER:
                _glWrapType = GL_CLAMP_TO_BORDER;
                break;
        }
        // init glFilterType
        switch (filterType) {
            case NEAREST:
                _glFilterType = GL_NEAREST;
                break;
            case LINEAR:
                _glFilterType = GL_LINEAR;
                break;
            case NEAREST_MIPMAP_NEAREST:
                _glFilterType = GL_NEAREST_MIPMAP_NEAREST;
                break;
            case LINEAR_MIPMAP_NEAREST:
                _glFilterType = GL_LINEAR_MIPMAP_NEAREST;
                break;
            case NEAREST_MIPMAP_LINEAR:
                _glFilterType = GL_NEAREST_MIPMAP_LINEAR;
                break;
            case LINEAR_MIPMAP_LINEAR:
                _glFilterType = GL_LINEAR_MIPMAP_LINEAR;
                break;
        }

        // bind texture
        glBindTexture(_glType, _textureId);

        // set texture wrap & filter type
        glTexParameteri(_glType, GL_TEXTURE_WRAP_S, _glWrapType);
        glTexParameteri(_glType, GL_TEXTURE_WRAP_T, _glWrapType);
        glTexParameteri(_glType, GL_TEXTURE_MIN_FILTER, _glFilterType);
        glTexParameteri(_glType, GL_TEXTURE_MAG_FILTER, _glFilterType);

        // Put image data to texture
        unsigned int format = _channels == 3 ? GL_RGB : GL_RGBA;
        // TODO 此处需要根据不同类型进行兼容, 例如 3D 贴图和天空盒贴图
        glTexImage2D(_glType, 0, (int) format, _width, _height, 0, format, GL_UNSIGNED_BYTE, _imgData);
        glGenerateMipmap(_glType);

        // release image data in memory
        stbi_image_free(_imgData);

        glBindTexture(_glType, GL_NONE);
    }

    const char *_name;
    unsigned int _textureId;
    unsigned char *_imgData;
    int _width, _height, _channels;
    unsigned int _glType;
    int _glWrapType, _glFilterType;
};


#endif //LEARNOPENGL_ENTITY_H
