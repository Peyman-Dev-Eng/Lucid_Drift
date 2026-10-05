#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <Renderer/Renderer.h>
#include <typeinfo>
#include <linux/input-event-codes.h>

namespace LDDrift
{
    class Scene
    {
    private:
        LDDrift::Renderer* renderer = nullptr;
        std::vector<LDDrift::Actors::Circle*> circleShapes;
        std::vector<LDDrift::Actors::Polygon*> polygonShapes;
        std::vector<LDDrift::Actors::Line> lines;
    public:
        Scene();
        void SetRenderer(LDDrift::Renderer* rendererPTR);
        void SendShapesToRender();
        void CreateCircleShape();
        void CreatePolygonShape();
        void CreateLineActor();
        ~Scene();
    };
}

#endif
