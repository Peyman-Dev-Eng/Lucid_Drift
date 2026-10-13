#include "Transform.h"
#include <Actors/Shapes/MainShape/Shape.h>

int LDDrift::Transform::widthScreen = VIEWPORT_WINDOW_WIDTH;
int LDDrift::Transform::heightScreen = VIEWPORT_WINDOW_HEIGHT;
int LDDrift::Transform::halfWidthScreen = HALF_VIEWPORT_WINDOW_WIDTH;
int LDDrift::Transform::halfHeightScreen = HALF_VIEWPORT_WINDOW_HEIGHT;

float LDDrift::Transform::TransformToNDC_Position(const float pointPos, const char posType) {
    if (posType == 'x' || posType == 'X') {
        return (pointPos - static_cast<float>(halfWidthScreen)) / static_cast<float>(halfWidthScreen);
    } else if (posType == 'y' || posType == 'Y') {
        return (pointPos - static_cast<float>(halfHeightScreen)) / static_cast<float>(halfHeightScreen);
    }
    constexpr bool posTypeInputArgumentFunctionIsNotAvailable = false;
    GLB_assert(posTypeInputArgumentFunctionIsNotAvailable);
}

float LDDrift::Transform::TransformToGlobalPosition(float pointPos, char posType) {
    if (posType == 'x' || posType == 'X') {
        return (pointPos + 1.0f) * static_cast<float>(halfWidthScreen);
    } else if (posType == 'y' || posType == 'Y') {
        return (pointPos + 1.0f) * static_cast<float>(halfHeightScreen);
    }
    constexpr bool posTypeInputArgumentFunctionIsNotAvailable = false;
    GLB_assert(posTypeInputArgumentFunctionIsNotAvailable);
}

std::vector<LDDrift::VecPos2D> LDDrift::Transform::TransformToNDC_Position(const LDDrift::Actors::Shape* shape) {
    std::vector<LDDrift::VecPos2D> NDC_pointPositon;
    for (const std::vector<LDDrift::VecPos2D>& points = shape->GetGlobalPoints();
         const LDDrift::VecPos2D& point : points) {
        NDC_pointPositon.push_back({
            (point.X - static_cast<float>(halfWidthScreen)) / static_cast<float>(halfWidthScreen),
            (point.Y - static_cast<float>(halfHeightScreen)) / static_cast<float>(halfHeightScreen)
        });
    }
    return NDC_pointPositon;
}

std::vector<LDDrift::VecPos2D> LDDrift::Transform::TransformToGlobalPosition(const LDDrift::Actors::Shape* shape) {
    std::vector<LDDrift::VecPos2D> globalPosition;
    for (const std::vector<LDDrift::VecPos2D>& points = shape->GetGlobalPoints();
         const LDDrift::VecPos2D& point : points) {
        globalPosition.push_back({
            (point.X + 1.0f) * static_cast<float>(halfWidthScreen),
            (point.Y + 1.0f) * static_cast<float>(halfHeightScreen)
        });
    }
    return globalPosition;
}

LDDrift::VecPos2D LDDrift::Transform::TransformToNDC_Position(const LDDrift::VecPos2D& point) {
    return LDDrift::VecPos2D{
        (point.X - static_cast<float>(halfWidthScreen)) / static_cast<float>(halfWidthScreen),
        (point.Y - static_cast<float>(halfHeightScreen)) / static_cast<float>(halfHeightScreen)
    };
}

LDDrift::VecPos2D LDDrift::Transform::TransformToGlobalPosition(const LDDrift::VecPos2D& point) {
    return LDDrift::VecPos2D{
        (point.X + 1.0f) * static_cast<float>(halfWidthScreen),
        (point.Y + 1.0f) * static_cast<float>(halfHeightScreen)
    };
}

std::vector<LDDrift::VecPos2D>
LDDrift::Transform::TransformToNDC_Position(const std::vector<LDDrift::VecPos2D>& points) {
    std::vector<LDDrift::VecPos2D> NDC_pointPositon;
    for (const LDDrift::VecPos2D& point : points) {
        NDC_pointPositon.push_back(LDDrift::Transform::TransformToNDC_Position(point));
    }
    return NDC_pointPositon;
}

std::vector<LDDrift::VecPos2D> LDDrift::Transform::TransformToGlobalPosition(
    const std::vector<LDDrift::VecPos2D>& points) {
    std::vector<LDDrift::VecPos2D> globalPointPosition;
    for (const LDDrift::VecPos2D& point : points) {
        globalPointPosition.push_back(LDDrift::Transform::TransformToGlobalPosition(point));
    }
    return globalPointPosition;
}

std::vector<LDDrift::Actors::Line::PNT> LDDrift::Transform::TransformToNDC_Position(
    const std::vector<LDDrift::Actors::Line::PNT>& points) {
    std::vector<LDDrift::Actors::Line::PNT> NDC_pointPositon;
    LDDrift::Actors::Line::PNT NDC_point;
    for (const auto& [Point_1, Point_2, Point_3] : points) {
        NDC_point.Point_1 = LDDrift::Transform::TransformToNDC_Position(Point_1);
        NDC_point.Point_2 = LDDrift::Transform::TransformToNDC_Position(Point_2);
        NDC_point.Point_3 = LDDrift::Transform::TransformToNDC_Position(Point_3);

        NDC_pointPositon.push_back(NDC_point);
    }
    return NDC_pointPositon;
}
