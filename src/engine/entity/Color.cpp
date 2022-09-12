//
// Created by SpriteLisen on 2022/9/12.
//

#include "Color.h"

Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

float Color::getRed() {
    return this->r;
}

float Color::getGreen() {
    return this->g;
}

float Color::getBlue() {
    return this->b;
}

float Color::getAlpha() {
    return this->a;
}