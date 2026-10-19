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
    newCircle.circle->SetScreenSize(core->window.GetViewportSize());
    newCircle.circle->SetRadius(static_cast<float>(_radius));
    newCircle.circle->SetSpeed(static_cast<float>(_speed));
    newCircle.circle->SetAllPointsColor(color);
    newCircle.circle->SetOriginalPositionToCenter();
    newCircle.circle->Rebuild();
    circleShapes.push_back({.circleName = newCircle.circleName, .circle = newCircle.circle});
}

LDDrift::Actors::Polygon* LDDrift::Scene::GetPolygon(const std::string& name) const {
    for (const auto& [polygonName, polygon] : polygonShapes) {
        if (polygonName == name) {
            return polygon;
        }
    }
    return nullptr;
}

void LDDrift::Scene::CreatePolygonShape(const std::string& name, const int _pointCount, const int _speed,
                                        const int* pos,
                                        const LDDrift::VecCol& color) {
    const POLYGON_SHAPE_INFORMATION newPolygon{.polygonName = name, .polygon = new LDDrift::Actors::Polygon()};
    newPolygon.polygon->SetPointCount(_pointCount);
    newPolygon.polygon->SetScreenSize(core->window.GetViewportSize());
    newPolygon.polygon->SetSpeed(static_cast<float>(_speed));
    newPolygon.polygon->SetAllPointsColor(color);
    for (int pointIndex = 0; pointIndex < _pointCount; ++pointIndex) {
        newPolygon.polygon->SetPoint(pointIndex, {
                                         static_cast<float>(pos[pointIndex * 2]),
                                         static_cast<float>(pos[pointIndex * 2 + 1])
                                     });
    }
    polygonShapes.push_back({.polygonName = newPolygon.polygonName, .polygon = newPolygon.polygon});
}

void LDDrift::Scene::CreateLineActor(const std::string& name, const int _thickness, const int* startPos,
                                     const int* endPos,
                                     const LDDrift::VecCol& color) {
    const LINE_ACTOR_INFORMATION newLine{
        .lineName = name, .line = new LDDrift::Actors::Line(
            {static_cast<float>(startPos[0]), static_cast<float>(startPos[1])},
            {static_cast<float>(endPos[0]), static_cast<float>(endPos[1])})
    };
    newLine.line->SetScreenSize(core->window.GetViewportSize());
    newLine.line->SetThickness(static_cast<float>(_thickness));
    newLine.line->SetLineColor(color);
    newLine.line->CreateTriangles();
    lines.push_back({.lineName = newLine.lineName, .line = newLine.line});
}

LDDrift::Actors::Line* LDDrift::Scene::GetLine(const std::string& name) const {
    for (const auto& [lineName, line] : lines) {
        if (lineName == name) {
            return line;
        }
    }
    return nullptr;
}

bool LDDrift::Scene::FindCircleWithName(const std::string& name) const {
    for (const auto& [lineName, line] : circleShapes) {
        if (lineName == name) {
            return true;
        }
    }
    return false;
}

bool LDDrift::Scene::FindPolygonWithName(const std::string& name) const {
    for (const auto& [polygonName, polygon] : polygonShapes) {
        if (polygonName == name) {
            return true;
        }
    }
    return false;
}

bool LDDrift::Scene::FindLineWithName(const std::string& name) const {
    for (const auto& [lineName, line] : lines) {
        if (lineName == name) {
            return true;
        }
    }
    return false;
}

void LDDrift::Scene::CreatePolygonShape(const std::string& name, int _pointCount, int _speed, const int* pos,
                                        const std::vector<LDDrift::VecCol>& colors) {
    const POLYGON_SHAPE_INFORMATION newPolygon{.polygonName = name, .polygon = new LDDrift::Actors::Polygon()};
    newPolygon.polygon->SetPointCount(_pointCount);
    newPolygon.polygon->SetScreenSize(core->window.GetViewportSize());
    newPolygon.polygon->SetSpeed(static_cast<float>(_speed));
    int counter = 0;
    for (const LDDrift::VecCol& color : colors) {
        newPolygon.polygon->SetPointColor(counter++, color);
    }
    for (int pointIndex = 0; pointIndex < _pointCount; ++pointIndex) {
        newPolygon.polygon->SetPoint(pointIndex, {
                                         static_cast<float>(pos[pointIndex * 2]),
                                         static_cast<float>(pos[pointIndex * 2 + 1])
                                     });
    }
    polygonShapes.push_back({.polygonName = newPolygon.polygonName, .polygon = newPolygon.polygon});
}
