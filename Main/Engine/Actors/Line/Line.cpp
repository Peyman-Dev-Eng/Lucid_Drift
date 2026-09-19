#include "Line.h"

LDDrift::Actors::Line::Line() = default;

LDDrift::Actors::Line::Line(const LDDrift::VecPos2D& FPoint, const LDDrift::VecPos2D& SPoint) :
    FirstPoint(FPoint), SecondPoint(SPoint), Thick(1) {}

LDDrift::Actors::Line& LDDrift::Actors::Line::CreateTriangles() {
    const float HalfThickness = Thick / 2.0f;
    LDDrift::VecPos2D Distance = LDDrift::VecPos2D::Normalize(SecondPoint - FirstPoint);
    const float SaveX = Distance.X;
    Distance.X = -Distance.Y;
    Distance.Y = SaveX;
    Distance *= HalfThickness;
    Points.push_back({
        .Point_1 = FirstPoint - Distance, .Point_2 = FirstPoint + Distance, .Point_3 = SecondPoint - Distance
    });
    Points.push_back({
        .Point_1 = FirstPoint + Distance, .Point_2 = SecondPoint - Distance, .Point_3 = SecondPoint + Distance
    });
    return *this;
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

std::vector<LDDrift::Actors::Line::PNT> LDDrift::Actors::Line::GetPoints() const {
    return Translate();
}

LDDrift::Actors::Line& LDDrift::Actors::Line::SetThickness(const float thick) {
    Thick = thick;
    return *this;
}

LDDrift::Actors::Line& LDDrift::Actors::Line::SetScreenSize(const LDDrift::VecPos2D& WindowSize) {
    WidthScreen = WindowSize.X;
    HeightScreen = WindowSize.Y;
    return *this;
}

std::vector<LDDrift::Actors::Line::PNT> LDDrift::Actors::Line::Translate() const {
    const float HalfWidth = WidthScreen / 2.0f;
    const float HalfHeight = HeightScreen / 2.0f;
    std::vector<LDDrift::Actors::Line::PNT> CopyPoints = Points;
    CopyPoints[0].Point_1.X = (CopyPoints[0].Point_1.X - HalfWidth) / HalfWidth;
    CopyPoints[0].Point_1.Y = (CopyPoints[0].Point_1.Y - HalfHeight) / HalfHeight;
    CopyPoints[0].Point_2.X = (CopyPoints[0].Point_2.X - HalfWidth) / HalfWidth;
    CopyPoints[0].Point_2.Y = (CopyPoints[0].Point_2.Y - HalfHeight) / HalfHeight;
    CopyPoints[0].Point_3.X = (CopyPoints[0].Point_3.X - HalfWidth) / HalfWidth;
    CopyPoints[0].Point_3.Y = (CopyPoints[0].Point_3.Y - HalfHeight) / HalfHeight;

    CopyPoints[1].Point_1.X = (CopyPoints[1].Point_1.X - HalfWidth) / HalfWidth;
    CopyPoints[1].Point_1.Y = (CopyPoints[1].Point_1.Y - HalfHeight) / HalfHeight;
    CopyPoints[1].Point_2.X = (CopyPoints[1].Point_2.X - HalfWidth) / HalfWidth;
    CopyPoints[1].Point_2.Y = (CopyPoints[1].Point_2.Y - HalfHeight) / HalfHeight;
    CopyPoints[1].Point_3.X = (CopyPoints[1].Point_3.X - HalfWidth) / HalfWidth;
    CopyPoints[1].Point_3.Y = (CopyPoints[1].Point_3.Y - HalfHeight) / HalfHeight;
    return CopyPoints;
}

LDDrift::Actors::Line::~Line() = default;
