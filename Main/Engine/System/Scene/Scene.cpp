#include "Scene.h"

#include "Actors/Shapes/Circle/CircleShape.h"

LDDrift::Scene::Scene() = default;

LDDrift::Scene::~Scene() = default;

void LDDrift::Scene::SetRenderer(LDDrift::Renderer* rendererPTR) {
    renderer = rendererPTR;
}

void LDDrift::Scene::CreateCircleShape() {
    circleShapes.push_back(new LDDrift::Actors::Circle());
}
