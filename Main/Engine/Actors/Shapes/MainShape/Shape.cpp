#include "Shape.h"

LDDrift::Actors::Shape::Shape() : screenSize(0, 0), OriginalPosition(0, 0), PointCount(0), Speed(0.01), FillShape(true),
                                  Thickness(0), HaveThickness(false) {}

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

void LDDrift::Actors::Shape::SetPointCount(const std::size_t point_count) {
    GLB_assert(point_count > PointCount && point_count >= 3)
    for (uint PointIndex = Points.empty() ? 0 : PointCount; PointIndex < point_count; ++PointIndex) {
        Points.emplace_back();
    }
    PointCount = point_count;
}

std::size_t LDDrift::Actors::Shape::GetPointCount() const {
    return PointCount;
}

void LDDrift::Actors::Shape::SetSpeed(const float spd) {
    Speed = spd;
}

void LDDrift::Actors::Shape::SetPoint(const std::size_t point_index, const LDDrift::VecPos2D& pos) {
    Points[point_index] = pos;
}

const LDDrift::VecPos2D& LDDrift::Actors::Shape::GetPoint(const std::size_t point_index) const {
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

const LDDrift::VecCol& LDDrift::Actors::Shape::GetPointColor(const std::size_t point_index) const {
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
    HaveThickness = true;
}

bool LDDrift::Actors::Shape::IsFillShape() const {
    return FillShape;
}

float LDDrift::Actors::Shape::GetThickness() const {
    return Thickness;
}

std::vector<LDDrift::VecPos2D> LDDrift::Actors::Shape::TransformPoints() const {
    const float halfWidthScreen = screenSize.X / 2;
    const float halfHeightScreen = screenSize.Y / 2;
    std::vector<LDDrift::VecPos2D> tPoints;
    tPoints.reserve(Points.size());
    std::size_t index = 0;
    for (const LDDrift::VecPos2D& point : Points) {
        tPoints.emplace_back();
        tPoints[index].X = (point.X - halfWidthScreen) / halfWidthScreen;
        tPoints[index].Y = (point.Y - halfHeightScreen) / halfHeightScreen;
        ++index;
    }
    return tPoints;
}

void LDDrift::Actors::Shape::SetScreenSize(const LDDrift::VecPos2D& size) {
    std::cout << "Hello\n";
    std::cout << size.X << ", " << size.Y << std::endl;
    screenSize = size;
}

const LDDrift::VecPos2D& LDDrift::Actors::Shape::GetScreenSize() const {
    return screenSize;
}

const std::vector<LDDrift::VecCol>& LDDrift::Actors::Shape::GetColorOfPoints() const {
    return ColorOfPoints;
}

bool LDDrift::Actors::Shape::IsHaveThickness() const {
    return HaveThickness;
}

LDDrift::Actors::Shape::isConvexData LDDrift::Actors::Shape::ShapeIsConvex() const {
    bool hasPositive = false;
    bool hasNegative = false;
    for (std::size_t point = 0; point < PointCount; ++point) {
        const LDDrift::VecPos2D& point_A = Points[point];
        const LDDrift::VecPos2D& point_B = Points[(point + 1) % PointCount];
        const LDDrift::VecPos2D& point_C = Points[(point + 2) % PointCount];
        const float cross =
            (point_B.X - point_A.X) * (point_C.Y - point_B.Y) -
            (point_B.Y - point_A.Y) * (point_C.X - point_B.X);
        if (cross > 0.0f) {
            hasPositive = true;
        }
        if (cross < 0.0f) {
            hasNegative = true;
        }
        if (hasPositive && hasNegative) {
            return {.isConvex = false, .pointDirection = 0};
        }
    }
    if (!hasPositive && !hasNegative) {
        return {.isConvex = false, .pointDirection = 0};
    }
    return {.isConvex = true, .pointDirection = hasNegative ? 1 : -1};
}

void LDDrift::Actors::Shape::SetAllPointsColor(const LDDrift::VecCol& targetColor) {
    ColorOfPoints.clear();
    ColorOfPoints.reserve(Points.size());
    for (std::size_t point = 0; point < Points.size(); ++point) {
        ColorOfPoints.push_back(targetColor);
    }
}

LDDrift::Actors::Shape::~Shape() = default;
