#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <Renderer/Renderer.h>
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

        struct LINE_ACTOR_INFORMATION
        {
            std::string lineName;
            LDDrift::Actors::Line* line;
        };

    private:
        bool sendDataToGPU = false;
        LDDrift::Core* core = nullptr;
        LDDrift::Renderer* renderer = nullptr;
        std::vector<CIRCLE_SHAPE_INFORMATION> circleShapes;
        std::vector<POLYGON_SHAPE_INFORMATION> polygonShapes;
        std::vector<LINE_ACTOR_INFORMATION> lines;

    public:
        Scene();
        void SetCorePTR(LDDrift::Core* corePtr);
        void MarkSendDataToGPU();
        void SetRendererPTR(LDDrift::Renderer* rendererPTR);
        void ReSendShapesToRender();
        // circle
        [[nodiscard]] bool FindCircleWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Circle* GetCircle(const std::string& name) const;
        void CreateCircleShape(const std::string& name,
                               int _pointCount,
                               int _radius,
                               int _speed,
                               const LDDrift::VecPos2D& pos,
                               const LDDrift::VecCol& color,
                               float thickness);
        bool DeleteCircleShape(const std::string& name);
        // polygon
        [[nodiscard]] bool FindPolygonWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Polygon* GetPolygon(const std::string& name) const;
        void CreatePolygonShape(const std::string& name,
                                int _pointCount,
                                int _speed,
                                const int* pos,
                                const LDDrift::VecCol& color);
        void CreatePolygonShape(const std::string& name,
                                int _pointCount,
                                int _speed,
                                const int* pos,
                                const std::vector<LDDrift::VecCol>& colors);
        bool DeletePolygonShape(const std::string& name);
        // Line
        [[nodiscard]] bool FindLineWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Line* GetLine(const std::string& name) const;
        void CreateLineActor(const std::string& name,
                             int _thickness,
                             const int* startPos,
                             const int* endPos,
                             const LDDrift::VecCol& color);
        bool DeleteLineShape(const std::string& name);
        ~Scene();
    };
}

#endif
