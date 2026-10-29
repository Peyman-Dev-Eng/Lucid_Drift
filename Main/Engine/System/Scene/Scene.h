#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Renderer/Renderer.h>
#include <thread>
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C 0x000001
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P 0x000002
#define LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L 0x000003

namespace LDDrift
{
    namespace Actors
    {
        class Shape;
        class Polygon;
        class Line;
        class Circle;
    }
    class Core;

    class Scene final
    {
    public:
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

    public:
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
        [[nodiscard]] std::vector<std::string> GetCircleNames() const;
        [[nodiscard]] std::vector<LDDrift::Actors::Circle*> GetCircles_ptr() const;
        // polygon
        [[nodiscard]] bool FindPolygonWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Polygon* GetPolygon(const std::string& name) const;
        void CreatePolygonShape(const std::string& name,
                                int _pointCount,
                                int _speed,
                                const int* pos,
                                const LDDrift::VecCol& color,
                                float thickness,
                                int joinLine_A);
        void CreatePolygonShape(const std::string& name,
                                int _pointCount,
                                int _speed,
                                const int* pos,
                                const std::vector<LDDrift::VecCol>& colors,
                                float thickness,
                                int joinLine_A);
        bool DeletePolygonShape(const std::string& name);
        [[nodiscard]] std::vector<std::string> GetPolygonNames() const;
        [[nodiscard]] std::vector<LDDrift::Actors::Polygon*> GetPolygons_ptr() const;
        // Line
        [[nodiscard]] bool FindLineWithName(const std::string& name) const;
        [[nodiscard]] LDDrift::Actors::Line* GetLine(const std::string& name) const;
        void CreateLineActor(const std::string& name,
                             int _thickness,
                             const int* startPos,
                             const int* endPos,
                             const LDDrift::VecCol& color);
        bool DeleteLineShape(const std::string& name);
        [[nodiscard]] std::vector<std::string> GetLineNames() const;
        [[nodiscard]] std::vector<LDDrift::Actors::Line*> GetLines_ptr() const;
        ~Scene();
    };
}

#endif
