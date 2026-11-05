#include "VecCol.h"

#include <ranges>

LDDrift::VecCol::VecCol() = default;

LDDrift::VecCol::VecCol(const float red, const float green, const float blue, const float alpha) {
    SetColor(red, green, blue, alpha);
}

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
    R = std::clamp(red, 0.0f, 1.0f);
    G = std::clamp(green, 0.0f, 1.0f);
    B = std::clamp(blue, 0.0f, 1.0f);
    A = std::clamp(alpha, 0.0f, 1.0f);
}

LDDrift::VecCol LDDrift::VecCol::operator-(const float& color) const {
    return VecCol{
        std::clamp(R - color, 0.0f, 1.0f),
        std::clamp(G - color, 0.0f, 1.0f),
        std::clamp(B - color, 0.0f, 1.0f),
        std::clamp(A - color, 0.0f, 1.0f)
    };
}

LDDrift::VecCol LDDrift::VecCol::operator+(const float& color) const {
    return VecCol{
        std::clamp(R + color, 0.0f, 1.0f),
        std::clamp(G + color, 0.0f, 1.0f),
        std::clamp(B + color, 0.0f, 1.0f),
        std::clamp(A + color, 0.0f, 1.0f)
    };
}

LDDrift::VecCol LDDrift::VecCol::operator*(const float& color) const {
    return VecCol{
        std::clamp(R * color, 0.0f, 1.0f),
        std::clamp(G * color, 0.0f, 1.0f),
        std::clamp(B * color, 0.0f, 1.0f),
        std::clamp(A * color, 0.0f, 1.0f)
    };
}

LDDrift::VecCol LDDrift::VecCol::operator/(const float& color) const {
    return VecCol{R / color, G / color, B / color, A / color};
}

LDDrift::VecCol& LDDrift::VecCol::operator-=(const float& color) {
    this->R = std::clamp(R - color, 0.0f, 1.0f);
    this->G = std::clamp(G - color, 0.0f, 1.0f);
    this->B = std::clamp(B - color, 0.0f, 1.0f);
    this->A = std::clamp(A - color, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator+=(const float& color) {
    this->R = std::clamp(R + color, 0.0f, 1.0f);
    this->G = std::clamp(G + color, 0.0f, 1.0f);
    this->B = std::clamp(B + color, 0.0f, 1.0f);
    this->A = std::clamp(A + color, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator*=(const float& color) {
    this->R = std::clamp(R * color, 0.0f, 1.0f);
    this->G = std::clamp(G * color, 0.0f, 1.0f);
    this->B = std::clamp(B * color, 0.0f, 1.0f);
    this->A = std::clamp(A * color, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator/=(const float& color) {
    this->R = std::clamp(R / color, 0.0f, 1.0f);
    this->G = std::clamp(G / color, 0.0f, 1.0f);
    this->B = std::clamp(B / color, 0.0f, 1.0f);
    this->A = std::clamp(A / color, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol LDDrift::VecCol::operator-(const VecCol& vec) const {
    return VecCol{
        std::clamp(R - vec.R, 0.0f, 1.0f),
        std::clamp(G - vec.G, 0.0f, 1.0f),
        std::clamp(B - vec.B, 0.0f, 1.0f),
        std::clamp(A - vec.A, 0.0f, 1.0f)
    };
}

LDDrift::VecCol LDDrift::VecCol::operator+(const VecCol& vec) const {
    return VecCol{
        std::clamp(R + vec.R, 0.0f, 1.0f),
        std::clamp(G + vec.G, 0.0f, 1.0f),
        std::clamp(B + vec.B, 0.0f, 1.0f),
        std::clamp(A + vec.A, 0.0f, 1.0f)
    };
}

LDDrift::VecCol LDDrift::VecCol::operator*(const VecCol& vec) const {
    return VecCol{
        std::clamp(R * vec.R, 0.0f, 1.0f),
        std::clamp(G * vec.G, 0.0f, 1.0f),
        std::clamp(B * vec.B, 0.0f, 1.0f),
        std::clamp(A * vec.A, 0.0f, 1.0f)
    };
}

LDDrift::VecCol LDDrift::VecCol::operator/(const VecCol& vec) const {
    return VecCol{
        std::clamp(R / vec.R, 0.0f, 1.0f),
        std::clamp(G / vec.G, 0.0f, 1.0f),
        std::clamp(B / vec.B, 0.0f, 1.0f),
        std::clamp(A / vec.A, 0.0f, 1.0f)
    };
}

LDDrift::VecCol& LDDrift::VecCol::operator-=(const VecCol& vec) {
    this->R = std::clamp(R + vec.R, 0.0f, 1.0f);
    this->G = std::clamp(G + vec.G, 0.0f, 1.0f);
    this->B = std::clamp(B + vec.B, 0.0f, 1.0f);
    this->A = std::clamp(A + vec.A, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator+=(const VecCol& vec) {
    this->R = std::clamp(R + vec.R, 0.0f, 1.0f);
    this->G = std::clamp(G + vec.G, 0.0f, 1.0f);
    this->B = std::clamp(B + vec.B, 0.0f, 1.0f);
    this->A = std::clamp(A + vec.B, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator*=(const VecCol& vec) {
    this->R = std::clamp(R + vec.R, 0.0f, 1.0f);
    this->G = std::clamp(G + vec.G, 0.0f, 1.0f);
    this->B = std::clamp(B + vec.B, 0.0f, 1.0f);
    this->A = std::clamp(A + vec.A, 0.0f, 1.0f);
    return *this;
}

LDDrift::VecCol& LDDrift::VecCol::operator/=(const VecCol& vec) {
    this->R = std::clamp(R + vec.R, 0.0f, 1.0f);
    this->G = std::clamp(G + vec.G, 0.0f, 1.0f);
    this->B = std::clamp(B + vec.B, 0.0f, 1.0f);
    this->A = std::clamp(A + vec.A, 0.0f, 1.0f);
    return *this;
}

bool LDDrift::VecCol::operator==(const VecCol& vec) const {
    return R == vec.R && G == vec.G && B == vec.B && A == vec.A;
}

bool LDDrift::VecCol::operator!=(const VecCol& vec) const {
    return !(*this == vec);
}

LDDrift::VecCol::~VecCol() = default;
