#include "CircleShape.h"

LDDrift::Actors::CircleShape::CircleShape() : radius(0), CenterPos(0, 0), Position(0, 0) {}

LDDrift::Actors::CircleShape::CircleShape(const float& R) : radius(R), CenterPos(0, 0), Position(0, 0) {
    this->SetPointCount(45);
    constexpr uint VectexAngle = 360.0f / 45.0f;
    uint PointIndex = 0;
    for (uint angle = 0; angle < 360; angle += VectexAngle, ++PointIndex) {
        const auto radians = static_cast<float>(angle * std::numbers::pi_v<double> / 180.0f);
        this->SetPoint(PointIndex, LDDrift::VecPos2D{
                           CenterPos.X + radius * std::cos(radians), CenterPos.Y + radius * std::sin(radians)
                       });
    }
}

void LDDrift::Actors::CircleShape::SetOriginalPositionToCenter() {
    this->SetOriginalPosition(CenterPos);
}

void LDDrift::Actors::CircleShape::SetRadius(const float& R) {
    radius = R;
}

void LDDrift::Actors::CircleShape::Rebuild() {
}

LDDrift::Actors::CircleShape::~CircleShape() = default;
