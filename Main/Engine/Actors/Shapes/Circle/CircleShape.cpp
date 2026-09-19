#include "CircleShape.h"

LDDrift::Actors::CircleShape::CircleShape() : radius(0), CenterPos(0, 0), Position(0, 0) {}

LDDrift::Actors::CircleShape::CircleShape(const float& R) : radius(R), CenterPos(0, 0), Position(0, 0) {
    this->SetPointCount(45);
    constexpr uint VectexAngle = 360.0f / 45.0f;
    uint PointIndex = 0;
    for (uint angle = 0; angle < 360; angle += VectexAngle, ++PointIndex) {
        const auto radians = static_cast<float>(angle * std::numbers::pi_v<double> / 180.0f);
        this->SetPoint(PointIndex, LDDrift::VecPos2D{
                           CenterPos.X + radiusNDC_X * std::cos(radians), CenterPos.Y + radiusNDC_Y * std::sin(radians)
                       });
    }
}

void LDDrift::Actors::CircleShape::SetOriginalPositionToCenter() {
    this->SetOriginalPosition(CenterPos);
}

void LDDrift::Actors::CircleShape::SetRadius(const float& R) {
    radius = R;
    const LDDrift::VecPos2D& ScreenSize = this->GetScreenSize();
    CTM_assert(ScreenSize.X != 0 && ScreenSize.Y != 0, "Screen size is null");
    radiusNDC_X = radius / this->GetScreenSize().X;
    radiusNDC_Y = radius / this->GetScreenSize().Y;
}

float LDDrift::Actors::CircleShape::GetRadius() const {
    return radius;
}

void LDDrift::Actors::CircleShape::Rebuild() {
    const uint VectexAngle = 360 / this->GetPointCount();
    uint PointIndex = 0;
    for (uint angle = 0; angle < 360; angle += VectexAngle, ++PointIndex) {
        const auto radians = static_cast<float>(angle * std::numbers::pi_v<double> / 180.0f);
        this->SetPoint(PointIndex, LDDrift::VecPos2D{
                           CenterPos.X + radiusNDC_X * std::cos(radians), CenterPos.Y + radiusNDC_Y * std::sin(radians)
                       });
    }
}

void LDDrift::Actors::CircleShape::Rotate(const Angle& angle) {}

LDDrift::Actors::CircleShape::~CircleShape() = default;
