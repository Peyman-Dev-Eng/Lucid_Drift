#include "VecPos.h"

LDDrift::VecPosition::VecPos2D::VecPos2D() = default;

LDDrift::VecPosition::VecPos2D::VecPos2D(const double x, const double y) {
    X = x;
    Y = y;
}

LDDrift::VecPosition::VecPos2D::VecPos2D(const std::initializer_list<double> list) {
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

LDDrift::VecPosition::VecPos2D LDDrift::VecPosition::VecPos2D::Normalize(const VecPos2D& vec) {
    VecPos2D NormalizedPoint = vec;
    const double length = std::sqrt(NormalizedPoint.X * NormalizedPoint.X + NormalizedPoint.Y * NormalizedPoint.Y);
    if (length == std::numeric_limits<double>::epsilon()) {
        return VecPos2D{0,0};
    }
    NormalizedPoint.X /= length;
    NormalizedPoint.Y /= length;
    return NormalizedPoint;
}

LDDrift::VecPosition::VecPos2D LDDrift::VecPosition::VecPos2D::NormalLine(const LDDrift::VecPosition::VecPos2D& FirstVec, const LDDrift::VecPosition::VecPos2D& SecondVec) {
    VecPos2D edge = FirstVec - SecondVec;
    edge = VecPos2D{-edge.Y, edge.X};
    return edge;
}


LDDrift::VecPosition::VecPos2D LDDrift::VecPosition::VecPos2D::operator-(const LDDrift::VecPosition::VecPos2D& vec2) const {
    return VecPos2D{this->X - vec2.X, this->Y - vec2.Y};
}

LDDrift::VecPosition::VecPos2D LDDrift::VecPosition::VecPos2D::operator+(const VecPos2D& vec2) const {
    return VecPos2D{this->X + vec2.X, this->Y + vec2.Y};
}

LDDrift::VecPosition::VecPos2D& LDDrift::VecPosition::VecPos2D::operator-=(const VecPos2D& vec2) {
    this->X -= vec2.X;
    this->Y -= vec2.Y;
    return *this;
}

LDDrift::VecPosition::VecPos2D& LDDrift::VecPosition::VecPos2D::operator+=(const VecPos2D& vec2) {
    this->X += vec2.X;
    this->Y += vec2.Y;
    return *this;
}

LDDrift::VecPosition::VecPos2D LDDrift::VecPosition::VecPos2D::operator*(const VecPos2D& vec2) const {
    return VecPos2D{this->X * vec2.X, this->Y * vec2.Y};
}

LDDrift::VecPosition::VecPos2D LDDrift::VecPosition::VecPos2D::operator/(const VecPos2D& vec2) const {
    return VecPos2D{this->X / vec2.X, this->Y / vec2.Y};
}

LDDrift::VecPosition::VecPos2D& LDDrift::VecPosition::VecPos2D::operator*=(const VecPos2D& vec2) {
    this->X *= vec2.X;
    this->Y *= vec2.Y;
    return *this;
}

LDDrift::VecPosition::VecPos2D& LDDrift::VecPosition::VecPos2D::operator/=(const VecPos2D& vec2) {
    this->X /= vec2.X;
    this->Y /= vec2.Y;
    return *this;
}

LDDrift::VecPosition::VecPos2D::~VecPos2D() = default;
