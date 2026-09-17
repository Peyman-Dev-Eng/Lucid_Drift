#include "VecCol.h"

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

LDDrift::VecCol::~VecCol() = default;
