#include "VecPos.h"

LDDrift::VecPos2D::VecPos2D() = default;

LDDrift::VecPos2D::VecPos2D(const float x, const float y) {
    X = x;
    Y = y;
}

LDDrift::VecPos2D::VecPos2D(const std::initializer_list<float> list) {
    GLB_assert(list.size() == 2)
    int counter = 0;
    for (const auto& elem : list) {
        if (counter == 0) {
            X = elem;
        } else {
            Y = elem;
        }
        ++counter;
    }
}

LDDrift::VecPos2D LDDrift::VecPos2D::Normalize(const VecPos2D& vec) {
    VecPos2D NormalizedPoint = vec;
    const float length = std::sqrt(NormalizedPoint.X * NormalizedPoint.X + NormalizedPoint.Y * NormalizedPoint.Y);
    if (length == std::numeric_limits<float>::epsilon() || length == 0.0f) {
        return VecPos2D{0, 0};
    }
    NormalizedPoint.X /= length;
    NormalizedPoint.Y /= length;
    return NormalizedPoint;
}

LDDrift::VecPos2D LDDrift::VecPos2D::NormalLine(const LDDrift::VecPos2D& FirstVec, const LDDrift::VecPos2D& SecondVec) {
    VecPos2D edge = FirstVec - SecondVec;
    edge = VecPos2D{-edge.Y, edge.X};
    return edge;
}


LDDrift::VecPos2D LDDrift::VecPos2D::operator-(const LDDrift::VecPos2D& vec2) const {
    return VecPos2D{this->X - vec2.X, this->Y - vec2.Y};
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator+(const VecPos2D& vec2) const {
    return VecPos2D{this->X + vec2.X, this->Y + vec2.Y};
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator-=(const VecPos2D& vec2) {
    this->X -= vec2.X;
    this->Y -= vec2.Y;
    return *this;
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator+=(const VecPos2D& vec2) {
    this->X += vec2.X;
    this->Y += vec2.Y;
    return *this;
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator*(const VecPos2D& vec2) const {
    return VecPos2D{this->X * vec2.X, this->Y * vec2.Y};
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator/(const VecPos2D& vec2) const {
    return VecPos2D{this->X / vec2.X, this->Y / vec2.Y};
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator*=(const VecPos2D& vec2) {
    this->X *= vec2.X;
    this->Y *= vec2.Y;
    return *this;
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator/=(const VecPos2D& vec2) {
    this->X /= vec2.X;
    this->Y /= vec2.Y;
    return *this;
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator-(const float& value) const {
    return VecPos2D{this->X - value, this->Y - value};
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator+(const float& value) const {
    return VecPos2D{this->X + value, this->Y + value};
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator-=(const float& value) {
    this->X -= value;
    this->Y -= value;
    return *this;
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator+=(const float& value) {
    this->X += value;
    this->Y += value;
    return *this;
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator*(const float& value) const {
    return VecPos2D{this->X * value, this->Y * value};
}

LDDrift::VecPos2D LDDrift::VecPos2D::operator/(const float& value) const {
    return VecPos2D{this->X / value, this->Y / value};
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator*=(const float& value) {
    this->X *= value;
    this->Y *= value;
    return *this;
}

LDDrift::VecPos2D& LDDrift::VecPos2D::operator/=(const float& value) {
    this->X /= value;
    this->Y /= value;
    return *this;
}

LDDrift::VecPos2D::~VecPos2D() = default;
