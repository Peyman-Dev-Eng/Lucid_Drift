#include "Scene.h"

#include "Actors/Shapes/Circle/CircleShape.h"
#include "System/Core/Core.h"

LDDrift::Scene::Scene() = default;

LDDrift::Scene::~Scene() {
    if (sendDataToRenderThread.joinable()) {
        sendDataToRenderThread.join();
    }
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
    if (sendDataToRenderThread.joinable()) {
        sendDataToRenderThread.join();
    }
    sendDataToRenderThread = std::thread([this]()
    {
        for (auto& [circleName, circle] : circleShapes) {
            renderer->AddShapeToRender(circle);
        }
        for (auto& [polygonName, polygon] : polygonShapes) {
            renderer->AddShapeToRender(polygon);
        }
        for (auto& [lineName, line] : lines) {
            renderer->AddLineToRender(line);
        }
    });
}

void LDDrift::Scene::CreateCircleShape(const std::string& name, int _pointCount, const int _radius,
                                       const LDDrift::VecCol& color) {
    CIRCLE_SHAPE_INFORMATION newCircle{.circleName = name, .circle = new LDDrift::Actors::Circle()};
    newCircle.circle->SetScreenSize(core->window.GetWindowSize());
    newCircle.circle->SetRadius(static_cast<float>(_radius));
}
