#include "VecCol.h"

#include <sys/cdefs.h>

LDDrift::VecCol::VecCol() = default;

LDDrift::VecCol::VecCol(const float red, const float green, const float blue, const float alpha) :
    R(red), G(green), B(blue), A(alpha) {}

void LDDrift::VecCol::Red() {
    R = 1.0f;
    B = 0.0f;
    G = 0.0f;
    A = 1.0f;
}

void LDDrift::VecCol::Green() {
    G = 1.0f;
    B = 0.0f;
    R = 0.0f;
    A = 1.0f;
}

void LDDrift::VecCol::Blue() {
    B = 1.0f;
    G = 0.0f;
    R = 0.0f;
    A = 0.0f;
}

void LDDrift::VecCol::White() {
    R = 1.0f;
    G = 1.0f;
    B = 1.0f;
    A = 1.0f;
}

void LDDrift::VecCol::Black() {
    R = 0.0f;
    G = 0.0f;
    B = 0.0f;
    A = 1.0f;
}

void LDDrift::VecCol::Yellow() {
    R = 1.0f;
    G = 1.0f;
    B = 0.0f;
    A = 1.0f;
}

void LDDrift::VecCol::Orange() {
    R = 1.0f;
    G = 0.5f;
    B = 0.0f;
    A = 1.0f;
}

void LDDrift::VecCol::Purple() {
    R = 0.5f;
    B = 0.0f;
    G = 0.5f;
    A = 1.0f;
}

void LDDrift::VecCol::SetColor(const float& red, const float& green, const float& blue, const float& alpha) {
    R = red;
    G = green;
    B = blue;
    A = alpha;
}

LDDrift::VecCol LDDrift::VecCol::operator-(const float& color) const {
    return VecCol{R - color, G - color, B - color, A - color};
}

LDDrift::VecCol LDDrift::VecCol::operator+(const float& color) const {
    return VecCol{R + color, G + color, B + color, A + color};
}

LDDrift::VecCol LDDrift::VecCol::operator*(const float& color) const {
    return VecCol{R * color, G * color, B * color, A * color};
}

LDDrift::VecCol LDDrift::VecCol::operator/(const float& color) const {
    return VecCol{R / color, G / color, B / color, A / color};
}

LDDrift::VecCol& LDDrift::VecCol::operator-=(const float& color) {
    this->R -= color;
    this->G -= color;
    this->B -= color;
    this->A -= color;
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator+=(const float& color) {
    this->R += color;
    this->G += color;
    this->B += color;
    this->A += color;
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator*=(const float& color) {
    this->R *= color;
    this->G *= color;
    this->B *= color;
    this->A *= color;
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator/=(const float& color) {
    this->R /= color;
    this->G /= color;
    this->B /= color;
    this->A /= color;
    return *this;
}

LDDrift::VecCol LDDrift::VecCol::operator-(const VecCol& vec) const {
    return VecCol{R - vec.R, G - vec.G, B - vec.B, A - vec.A};
}

LDDrift::VecCol LDDrift::VecCol::operator+(const VecCol& vec) const {
    return VecCol{R + vec.R, G + vec.G, B + vec.B, A + vec.A};
}

LDDrift::VecCol LDDrift::VecCol::operator*(const VecCol& vec) const {
    return VecCol{R * vec.R, G * vec.G, B * vec.B, A * vec.A};
}

LDDrift::VecCol LDDrift::VecCol::operator/(const VecCol& vec) const {
    return VecCol{R / vec.R, G / vec.G, B / vec.B, A / vec.A};
}

LDDrift::VecCol& LDDrift::VecCol::operator-=(const VecCol& vec) {
    this->R -= vec.R;
    this->G -= vec.G;
    this->B -= vec.B;
    this->A -= vec.A;
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator+=(const VecCol& vec) {
    this->R += vec.R;
    this->G += vec.G;
    this->B += vec.B;
    this->A += vec.A;
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator*=(const VecCol& vec) {
    this->R *= vec.R;
    this->G *= vec.G;
    this->B *= vec.B;
    this->A *= vec.A;
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator/=(const VecCol& vec) {
    this->R /= vec.R;
    this->G /= vec.G;
    this->B /= vec.B;
    this->A /= vec.A;
    return *this;
}

LDDrift::VecCol::~VecCol() = default;
