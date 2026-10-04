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
        std::vector<LDDrift::Actors::Shape*> shapes;
        std::vector<LDDrift::Actors::Line> lines;
    public:
        Scene();
        void SetRenderer(LDDrift::Renderer* rendererPTR);
        template <typename ShapeTypeClass>
        void Create(const ShapeTypeClass* shape);
        void SendShapesToRender();
        ~Scene();
    };
}

#endif
