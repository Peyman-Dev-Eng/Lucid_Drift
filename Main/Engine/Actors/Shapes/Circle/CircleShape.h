#ifndef LUCID_DRIFT_CIRCLESHAPE_H
#define LUCID_DRIFT_CIRCLESHAPE_H
#include <linux/input.h>

#include "../MainShape/Shape.h"

namespace LDDrift::Actors
{
    class CircleShape final : public LDDrift::Actors::Shape
    {
    private:
        float radius;
        LDDrift::VecPos2D CenterPos;
        LDDrift::VecPos2D Position;

    public:
        CircleShape();
        explicit CircleShape(const float& R);
        void SetRadius(const float& R);
        void SetOriginalPositionToCenter();
        void Rebuild() override;
        ~CircleShape() override;
    };
}

#endif