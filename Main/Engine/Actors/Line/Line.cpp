#include "Line.h"

LDDrift::Actors::Line::Line() = default;

LDDrift::Actors::Line::Line(const LDDrift::VecPos2D& FPoint, const LDDrift::VecPos2D& SPoint) :
    FirstPoint(FPoint), SecondPoint(SPoint), Thick(1) {}

void LDDrift::Actors::Line::CreateTriangles() {
    const float HalfThickness = Thick / 2.0f;
    LDDrift::VecPos2D Distance = LDDrift::VecPos2D::Normalize(SecondPoint - FirstPoint);
    Distance.X = -Distance.Y;
    Distance.Y = Distance.X;
    Distance *= HalfThickness;
    Points.push_back({.Point_1 = FirstPoint - Distance, .Point_2 = FirstPoint + Distance, .Point_3 = SecondPoint - Distance});
    Points.push_back({.Point_1 = FirstPoint + Distance, .Point_2 = SecondPoint - Distance, .Point_3 = SecondPoint + Distance});
}

void LDDrift::Actors::Line::SetFirstPoint(const LDDrift::VecPos2D& FPoint) {
    FirstPoint = FPoint;
}

void LDDrift::Actors::Line::SetSecondPoint(const LDDrift::VecPos2D& SPoint) {
    SecondPoint = SPoint;
}

LDDrift::VecPos2D LDDrift::Actors::Line::GetFirstPoint() const {
    return FirstPoint;
}

LDDrift::VecPos2D LDDrift::Actors::Line::GetSecondPoint() const {
    return SecondPoint;
}

LDDrift::Actors::Line::~Line() = default;
