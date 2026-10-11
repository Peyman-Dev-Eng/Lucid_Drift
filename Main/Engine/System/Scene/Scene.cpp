#include "Scene.h"

#include "Actors/Shapes/Circle/CircleShape.h"
#include "System/Core/Core.h"

LDDrift::Scene::Scene() = default;

LDDrift::Scene::~Scene() {
    for (auto& [circleName, circle] : circleShapes) {
        delete circle;
    }
    for (auto& [polygonName, polygon] : polygonShapes) {
        delete polygon;
    }
    for (auto& [lineName, line] : lines) {
        delete line;
    }
}

void LDDrift::Scene::SetCorePTR(LDDrift::Core* corePtr) {
    NPV_assert(corePtr != nullptr);
    core = corePtr;
}

void LDDrift::Scene::SetRendererPTR(LDDrift::Renderer* rendererPTR) {
    NPV_assert(rendererPTR != nullptr);
    renderer = rendererPTR;
}

void LDDrift::Scene::SendShapesToRender() {
    NPV_assert(renderer != nullptr)

    for (auto& [circleName, circle] : circleShapes) {
        renderer->AddShapeToRender(circle);
    }
    for (auto& [polygonName, polygon] : polygonShapes) {
        renderer->AddShapeToRender(polygon);
    }
    for (auto& [lineName, line] : lines) {
        renderer->AddLineToRender(line);
    }
    renderer->UpdateShapeData();
    renderer->SendDataToGPU();
}

LDDrift::Actors::Circle* LDDrift::Scene::GetCircle(const std::string& name) const {
    for (const auto& [circleName, circle] : circleShapes) {
        if (circleName == name) {
            return circle;
        }
    }
    return nullptr;
}

void LDDrift::Scene::CreateCircleShape(const std::string& name, const int _pointCount, const int _radius,
                                       const int _speed, const LDDrift::VecPos2D& pos, const LDDrift::VecCol& color) {
    const CIRCLE_SHAPE_INFORMATION newCircle{.circleName = name, .circle = new LDDrift::Actors::Circle()};
    newCircle.circle->SetCirclePosition(pos);
    newCircle.circle->SetPointCount(_pointCount);
    newCircle.circle->SetScreenSize(core->window.GetWindowSize());
    newCircle.circle->SetRadius(static_cast<float>(_radius));
    newCircle.circle->SetSpeed(static_cast<float>(_speed));
    newCircle.circle->SetAllPointsColor(color);
    newCircle.circle->SetOriginalPositionToCenter();
    newCircle.circle->Rebuild();
    circleShapes.push_back({.circleName = newCircle.circleName, .circle = newCircle.circle});
}
