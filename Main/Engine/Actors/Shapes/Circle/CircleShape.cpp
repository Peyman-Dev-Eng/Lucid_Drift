#include "CircleShape.h"

LDDrift::Actors::Circle::Circle() : radiusNDC_X(0), radiusNDC_Y(0), radius(0), CenterPos(0, 0), Position(0, 0) {}

LDDrift::Actors::Circle::Circle(const float& R) : radiusNDC_X(0), radiusNDC_Y(0), radius(R),
                                                  CenterPos(0, 0), Position(0, 0) {
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

void LDDrift::Actors::Circle::SetOriginalPositionToCenter() {
    this->SetOriginalPosition(CenterPos);
}

void LDDrift::Actors::Circle::SetRadius(const float& R) {
    radius = R;
    const LDDrift::VecPos2D& ScreenSize = this->GetScreenSize();
    CTM_assert(ScreenSize.X != 0 && ScreenSize.Y != 0, "Screen size is null");
    radiusNDC_X = radius / this->GetScreenSize().X;
    radiusNDC_Y = radius / this->GetScreenSize().Y;
}

float LDDrift::Actors::Circle::GetRadius() const {
    return radius;
}

std::vector<float> LDDrift::Actors::Circle::CreateTriangles() const {
    std::vector<float> verticesOfTriangles;
    std::size_t vertexNumber = 0;
    const std::size_t lastIndex = this->GetPointCount() - 1;
    const std::vector<LDDrift::VecCol>& verticesColor = this->GetColorOfPoints();
    for (const std::vector<LDDrift::VecPos2D>& points = this->GetPoints();
         const LDDrift::VecPos2D& point : points) {
        verticesOfTriangles.push_back(CenterPos.X);
        verticesOfTriangles.push_back(CenterPos.Y);
        verticesOfTriangles.push_back(0.0f);
        verticesOfTriangles.push_back(point.X);
        verticesOfTriangles.push_back(point.Y);
        verticesOfTriangles.push_back(0.0f);
        if (vertexNumber == lastIndex) {
            verticesOfTriangles.push_back(points[0].X);
            verticesOfTriangles.push_back(points[0].Y);
            verticesOfTriangles.push_back(0.0f);
        } else {
            verticesOfTriangles.push_back(points[vertexNumber + 1].X);
            verticesOfTriangles.push_back(points[vertexNumber + 1].Y);
            verticesOfTriangles.push_back(0.0f);
        }
        ++vertexNumber;
    }
    return verticesOfTriangles;
}

LDDrift::VecCol LDDrift::Actors::Circle::CalculateAverageVertexColor() const {
    if (this->IsFillShape()) {
        return this->GetPointColor(0);
    }
    else {
        LDDrift::VecCol sumColor;
    }
}

void LDDrift::Actors::Circle::Rebuild() {
    const uint VectexAngle = 360 / this->GetPointCount();
    uint PointIndex = 0;
    for (uint angle = 0; angle < 360; angle += VectexAngle, ++PointIndex) {
        const auto radians = static_cast<float>(angle * std::numbers::pi_v<double> / 180.0f);
        this->SetPoint(PointIndex, LDDrift::VecPos2D{
                           CenterPos.X + radiusNDC_X * std::cos(radians), CenterPos.Y + radiusNDC_Y * std::sin(radians)
                       });
    }
}

void LDDrift::Actors::Circle::Rotate(const Angle& angle) {}

LDDrift::Actors::Circle::~Circle() = default;
