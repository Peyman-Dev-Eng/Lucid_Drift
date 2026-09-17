#include "VecPos.h"

VecPos2D::VecPos2D() = default;

VecPos2D::VecPos2D(const double x, const double y) {
    X = x;
    Y = y;
}

VecPos2D::VecPos2D(const std::initializer_list<double> list) {
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

VecPos2D VecPos2D::Normalize(const VecPos2D& vec) {
    VecPos2D NormalizedPoint = vec;
    const double length = std::sqrt(NormalizedPoint.X * NormalizedPoint.X + NormalizedPoint.Y * NormalizedPoint.Y);
    if (length == std::numeric_limits<double>::epsilon()) {
        return VecPos2D{0,0};
    }
    NormalizedPoint.X /= length;
    NormalizedPoint.Y /= length;
    return NormalizedPoint;
}

VecPos2D VecPos2D::NormalLine(const VecPos2D& FirstVec, const VecPos2D& SecondVec) {
    VecPos2D edge = FirstVec - SecondVec;
    edge = VecPos2D{-edge.Y, edge.X};
    return edge;
}


VecPos2D VecPos2D::operator-(const VecPos2D& vec2) const {
    return VecPos2D{this->X - vec2.X, this->Y - vec2.Y};
}

VecPos2D VecPos2D::operator+(const VecPos2D& vec2) const {
    return VecPos2D{this->X + vec2.X, this->Y + vec2.Y};
}

VecPos2D& VecPos2D::operator-=(const VecPos2D& vec2) {
    this->X -= vec2.X;
    this->Y -= vec2.Y;
    return *this;
}

VecPos2D& VecPos2D::operator+=(const VecPos2D& vec2) {
    this->X += vec2.X;
    this->Y += vec2.Y;
    return *this;
}

VecPos2D VecPos2D::operator*(const VecPos2D& vec2) const {
    return VecPos2D{this->X * vec2.X, this->Y * vec2.Y};
}

VecPos2D VecPos2D::operator/(const VecPos2D& vec2) const {
    return VecPos2D{this->X / vec2.X, this->Y / vec2.Y};
}

VecPos2D& VecPos2D::operator*=(const VecPos2D& vec2) {
    this->X *= vec2.X;
    this->Y *= vec2.Y;
    return *this;
}

VecPos2D& VecPos2D::operator/=(const VecPos2D& vec2) {
    this->X /= vec2.X;
    this->Y /= vec2.Y;
    return *this;
}

VecPos2D::~VecPos2D() = default;
