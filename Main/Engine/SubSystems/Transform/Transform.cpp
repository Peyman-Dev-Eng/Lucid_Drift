#include "Transform.h"
#include <Actors/Shapes/MainShape/Shape.h>

int LDDrift::Transform::widthScreen = VIEWPORT_WINDOW_WIDTH;
int LDDrift::Transform::heightScreen = VIEWPORT_WINDOW_HEIGHT;
int LDDrift::Transform::halfWidthScreen = HALF_VIEWPORT_WINDOW_WIDTH;
int LDDrift::Transform::halfHeightScreen = HALF_VIEWPORT_WINDOW_HEIGHT;

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
