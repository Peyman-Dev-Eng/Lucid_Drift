#include "Shape.h"

LDDrift::Actors::Shape::Shape() : screenSize(0,0), OriginalPosition(0, 0), PointCount(0), Speed(0.01), FillShape(true), Thickness(0) {}

void LDDrift::Actors::Shape::MoveUp() {
    for (VecPos2D& point : Points) {
        point.Y += Speed;
    }
}

void LDDrift::Actors::Shape::MoveDown() {
    for (VecPos2D& point : Points) {
        point.Y -= Speed;
    }
}

void LDDrift::Actors::Shape::MoveLeft() {
    for (VecPos2D& point : Points) {
        point.X -= Speed;
    }
}

void LDDrift::Actors::Shape::MoveRight() {
    for (VecPos2D& point : Points) {
        point.X += Speed;
    }
}

void LDDrift::Actors::Shape::SetOriginalPosition(const LDDrift::VecPos2D& pos) {
    OriginalPosition.X = pos.X;
    OriginalPosition.Y = pos.Y;
}

void LDDrift::Actors::Shape::Rotate(const Angle& angle) {
    const float radians = angle.GetAngleRadians();
    for (VecPos2D& point : Points) {
        const float dx = point.X - OriginalPosition.X;
        const float dy = point.Y - OriginalPosition.Y;
        point.X = dx * std::cos(radians) - dy * std::sin(radians);
        point.Y = dx * std::sin(radians) + dy * std::cos(radians);
        point += OriginalPosition;
    }
}

void LDDrift::Actors::Shape::SetPointCount(const uint point_count) {
    if (point_count <= PointCount) {
        Points.clear();
    }
    for (uint PointIndex = Points.empty() ? 0 : PointCount; PointIndex < point_count; ++PointIndex) {
        Points.emplace_back();
    }
    PointCount = point_count;
}

uint LDDrift::Actors::Shape::GetPointCount() const {
    return PointCount;
}

void LDDrift::Actors::Shape::SetSpeed(const float spd) {
    Speed = spd;
}

void LDDrift::Actors::Shape::SetPoint(const uint point_index, const LDDrift::VecPos2D& pos) {
    Points[point_index] = pos;
}

const LDDrift::VecPos2D& LDDrift::Actors::Shape::GetPoint(const uint point_index) const {
    OOR_assert(point_index >= 0 && point_index < Points.size());
    return Points[point_index];
}

void LDDrift::Actors::Shape::SetPointColor(const uint point_index, const LDDrift::VecCol& color) {
    OOR_assert(point_index >= 0 && point_index < Points.size());
    if (ColorOfPoints.empty()) {
        ColorOfPoints.reserve(PointCount);
        for (uint index = 0; index < PointCount; ++index) {
            ColorOfPoints.emplace_back();
        }
    }
    ColorOfPoints[point_index] = color;
}

const LDDrift::VecPos2D& LDDrift::Actors::Shape::GetOriginalPosition() const {
    return OriginalPosition;
}

const LDDrift::VecCol& LDDrift::Actors::Shape::GetPointColor(const uint point_index) const {
    OOR_assert(point_index >= 0 && point_index < Points.size());
    return ColorOfPoints[point_index];
}

void LDDrift::Actors::Shape::Move(const Dir direction) {
    if (direction == Dir::UP) {
        this->MoveUp();
        return;
    } else if (direction == Dir::DOWN) {
        this->MoveDown();
        return;
    } else if (direction == Dir::LEFT) {
        this->MoveLeft();
        return;
    } else if (direction == Dir::RIGHT) {
        this->MoveRight();
        return;
    }
}

const std::vector<LDDrift::VecPos2D>& LDDrift::Actors::Shape::GetPoints() const {
    return Points;
}

void LDDrift::Actors::Shape::ResetPointCount() {
    PointCount = 0;
}

void LDDrift::Actors::Shape::ResetPoints() {
    Points.clear();
}

void LDDrift::Actors::Shape::ResetColorOfPoints() {
    ColorOfPoints.clear();
}

void LDDrift::Actors::Shape::ResetOriginalPosition() {
    OriginalPosition.X = Points[0].X;
    OriginalPosition.Y = Points[0].Y;
}


void LDDrift::Actors::Shape::SetPosition(const LDDrift::VecPos2D& pos) {
    for (LDDrift::VecPos2D& point : Points) {
        point += pos;
    }
}

void LDDrift::Actors::Shape::SetFillColor(const bool IsFillShape) {
    FillShape = IsFillShape;
}

void LDDrift::Actors::Shape::SetThickness(const float thickness) {
    GLB_assert(thickness >= 0.0f)
    Thickness = thickness;
}

bool LDDrift::Actors::Shape::IsFillShape() const {
    return FillShape;
}

float LDDrift::Actors::Shape::GetThickness() const {
    return Thickness;
}

void LDDrift::Actors::Shape::SetScreenSize(const LDDrift::VecPos2D& size) {
    screenSize = size;
}

const LDDrift::VecPos2D& LDDrift::Actors::Shape::GetScreenSize() const {
    return screenSize;
}

LDDrift::Actors::Shape::~Shape() = default;
