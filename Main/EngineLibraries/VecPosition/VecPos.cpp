#include "VecPos.h"
#include "../Engine/System/Triangulation/Triangulation.h"

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
    if (length == 0.0f) {
        return VecPos2D{0.0f, 0.0f};
    }
    NormalizedPoint.X /= length;
    NormalizedPoint.Y /= length;
    return NormalizedPoint;
}

LDDrift::VecPos2D LDDrift::VecPos2D::NormalLine(const LDDrift::VecPos2D& FirstVec, const LDDrift::VecPos2D& SecondVec,
                                                const char& dir) {
    const VecPos2D edge = LDDrift::VecPos2D::Normalize(FirstVec - SecondVec);
    if (dir == 'u' || dir == 'U') {
        return VecPos2D{-edge.Y, edge.X};
    } else if (dir == 'd' || dir == 'D') {
        return VecPos2D{edge.Y, -edge.X};
    }
    CTM_assert(false, "direction input for normalize line is invalid")
}

#include <cmath>
#include <algorithm>

float LDDrift::VecPos2D::AngleBetween(
    const VecPos2D& origin,
    const VecPos2D& a,
    const VecPos2D& b)
{
    const float ax = a.X - origin.X;
    const float ay = a.Y - origin.Y;

    const float bx = b.X - origin.X;
    const float by = b.Y - origin.Y;

    const float dot = ax * bx + ay * by;

    const float lenA = std::sqrt(ax * ax + ay * ay);
    const float lenB = std::sqrt(bx * bx + by * by);

    if (lenA == 0.0f || lenB == 0.0f)
        return 0.0f;

    const float cosine = std::clamp(
        dot / (lenA * lenB),
        -1.0f,
        1.0f
    );

    return std::acos(cosine) * 180.0f / std::acos(-1.0f);
}

LDDrift::VecPos2D LDDrift::VecPos2D::NormalLine(const VecPos2D& FirstVec, const VecPos2D& SecondVec) {
    const VecPos2D edge = LDDrift::VecPos2D::Normalize(FirstVec - SecondVec);
    return VecPos2D{-edge.Y, edge.X};
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

bool LDDrift::VecPos2D::operator==(const VecPos2D& vec) const {
    return this->X == vec.X && this->Y == vec.Y;
}

bool LDDrift::VecPos2D::operator!=(const VecPos2D&) const {
    return this->X != this->X || this->Y != this->Y;
}

LDDrift::VecPos2D::~VecPos2D() = default;
