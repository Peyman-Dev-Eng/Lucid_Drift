#include "Scene.h"

#include "Actors/Shapes/Circle/CircleShape.h"

LDDrift::Scene::Scene() = default;

LDDrift::Scene::~Scene() = default;

template <typename ShapeTypeClass>
void LDDrift::Scene::Create(const ShapeTypeClass* shape) {
    if (typeid(*shape) == typeid(LDDrift::Actors::Line)) {
        lines.push_back(shape);
        return;
    } else if (typeid(*shape) == typeid(LDDrift::Actors::Circle) ||
        typeid(*shape) == typeid(LDDrift::Actors::Polygon)) {
        shapes.push_back(shape);
        return;
    } else {
        std::cout << "Not Available shape type" << std::endl;
    }
}
