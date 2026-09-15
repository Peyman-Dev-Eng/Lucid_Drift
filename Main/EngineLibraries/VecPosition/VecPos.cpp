#include "VecPos.h"

VecPos2D::VecPos2D() = default;

VecPos2D::VecPos2D(const double x, const double y) {
    X = x;
    Y = y;
}

VecPos2D::VecPos2D(std::initializer_list<double> list) {
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

VecPos2D VecPos2D::operator-(const VecPos2D& vec2) const {
    return VecPos2D{this->X - vec2.X, this->Y - vec2.Y};
}


VecPos2D::~VecPos2D() = default;
