//
// Created by SpriteLisen on 2022/9/12.
//

#ifndef LEARNOPENGL_COLOR_H
#define LEARNOPENGL_COLOR_H


class Color {
public:
    Color(float r, float g, float b, float a = 1.0f);
    float getRed();
    float getGreen();
    float getBlue();
    float getAlpha();

private:
    float r, g, b, a;
};


#endif //LEARNOPENGL_COLOR_H
