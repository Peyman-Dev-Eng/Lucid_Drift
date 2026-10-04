#ifndef LUCID_DRIFT_TRANSFORM_H
#define LUCID_DRIFT_TRANSFORM_H
#include <vector>
#include <VecPos.h>
#include <System/Window/Window.h>
#include <Actors/Line/Line.h>

namespace LDDrift
{
    namespace Actors
    {
        class Shape;
    }
    class Transform
    {
    public:
        static int widthScreen;
        static int heightScreen;
        static int halfWidthScreen;
        static int halfHeightScreen;
        static std::vector<LDDrift::VecPos2D> TransformToNDC_Position(const LDDrift::Actors::Shape*);
        static std::vector<LDDrift::VecPos2D> TransformToGlobalPosition(const LDDrift::Actors::Shape*);
        static LDDrift::VecPos2D TransformToNDC_Position(const LDDrift::VecPos2D&);
        static LDDrift::VecPos2D TransformToGlobalPosition(const LDDrift::VecPos2D&);
    };
}

#endif
