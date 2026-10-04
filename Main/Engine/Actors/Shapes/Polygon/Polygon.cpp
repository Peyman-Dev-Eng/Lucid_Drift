#include "Polygon.h"

LDDrift::Actors::Polygon::Polygon() = default;

LDDrift::VecCol LDDrift::Actors::Polygon::CalculateAverageVertexColor() const {
    CTM_assert(this->ShapeIsConvex().isConvex, "this is shape is not a convex polygon");
    LDDrift::VecCol resultColor;
    const std::vector<LDDrift::VecCol>& verticesColor = this->GetColorOfPoints();
    const std::size_t pointCount = this->GetPointCount();
    for (std::size_t point = 0; point < this->GetPointCount(); ++point) {
        resultColor += verticesColor[point];
    }
    resultColor /= static_cast<float>(pointCount);
    return resultColor;
}

void LDDrift::Actors::Polygon::Rebuild() {
    this->SetOriginalPosition(this->CalculateAveragePointPosition());
}

void LDDrift::Actors::Polygon::Rebuild(int width, int height) {
    this->SetScreenSize({static_cast<float>(width), static_cast<float>(height)});
}

LDDrift::Actors::Polygon::~Polygon() = default;
