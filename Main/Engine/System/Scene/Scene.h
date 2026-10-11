#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <Renderer/Renderer.h>
#include <typeinfo>
#include <thread>
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
            LDDrift::Actors::Circle* circle;
        };

        struct POLYGON_SHAPE_INFORMATION
        {
            std::string polygonName;
            LDDrift::Actors::Polygon* polygon;
        };

        struct LINE_SHAPE_INFORMATION
        {
            std::string lineName;
            LDDrift::Actors::Line* line;
        };

        std::thread sendDataToRenderThread;

    private:
        LDDrift::Core* core = nullptr;
        LDDrift::Renderer* renderer = nullptr;
        std::vector<CIRCLE_SHAPE_INFORMATION> circleShapes;
        std::vector<POLYGON_SHAPE_INFORMATION> polygonShapes;
        std::vector<LINE_SHAPE_INFORMATION> lines;
        int circleCount = 0;
        int polygonCount = 0;
        int lineCount = 0;

    public:
        Scene();
        void SetCorePTR(LDDrift::Core* corePtr);
        void SetRendererPTR(LDDrift::Renderer* rendererPTR);
        void SendShapesToRender();
        void CreateCircleShape(const std::string& name,
                               int _pointCount,
                               int _radius,
                               const LDDrift::VecCol& color);
        void CreatePolygonShape();
        void CreateLineActor();
        ~Scene();
    };
}

#endif
