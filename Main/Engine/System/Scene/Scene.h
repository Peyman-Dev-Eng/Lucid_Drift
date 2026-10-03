#ifndef LUCID_DRIFT_SCENE_SYSTEM_H
#define LUCID_DRIFT_SCENE_SYSTEM_H
#include <vector>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <typeinfo>

namespace LDDrift
{
    class Scene
    {
    private:
        std::vector<LDDrift::Actors::Shape*> shapes;
        std::vector<LDDrift::Actors::Line> lines;
    public:
        Scene();
        template <typename ShapeTypeClass>
        void Create(const ShapeTypeClass* shape);
        ~Scene();
    };
}

#endif
