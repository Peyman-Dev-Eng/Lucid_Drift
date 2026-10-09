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
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C 0x000001
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P 0x000002
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L 0x000003

namespace LDDrift
{
    class Scene
    {
    private:
        struct CIRCLE_SHAPE_INFORMATION
        {
            std::string circleName;
            float radiusOfCircle;
            float pointCount;
            std::vector<LDDrift::VecCol> pointColors;
        };

    private:
        LDDrift::Renderer* renderer = nullptr;
        std::vector<LDDrift::Actors::Circle*> circleShapes;
        std::vector<LDDrift::Actors::Polygon*> polygonShapes;
        std::vector<LDDrift::Actors::Line*> lines;
        int circleCount = 0;
        int polygonCount = 0;
        int lineCount = 0;

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
