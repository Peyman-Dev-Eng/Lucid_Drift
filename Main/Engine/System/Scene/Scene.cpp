#include "Scene.h"

#include "Actors/Shapes/Circle/CircleShape.h"

LDDrift::Scene::Scene() = default;

LDDrift::Scene::~Scene() = default;

void LDDrift::Scene::SetRenderer(LDDrift::Renderer* rendererPTR) {
    renderer = rendererPTR;
}

void LDDrift::Scene::SendShapesToRender() {
    NPV_assert(renderer != nullptr)
    for (LDDrift::Actors::Circle* circle : circleShapes) {
        renderer->AddShapeToRender(circle);
    }
    for (LDDrift::Actors::Polygon* polygon : polygonShapes) {
        renderer->AddShapeToRender(polygon);
    }
    for (LDDrift::Actors::Line* line : lines) {
        renderer->AddLineToRender(line);
    }
}

void LDDrift::Scene::CreateCircleShape() {

}
