#ifndef LUCID_DRIFT_CIRCLESHAPE_H
#define LUCID_DRIFT_CIRCLESHAPE_H
#include "../MainShape/Shape.h"

namespace LDDrift::Actors
{
    /**
     * CircleShape class represents a geometric circle shape.
     *
     * @class CircleShape
     * @brief A class for representing and manipulating a circle shape.
     *
     * This class extends the base Shape class to represent a circle shape with a radius.
     * It provides methods for setting the radius, rotating the circle, and rebuilding the shape.
     * The CircleShape class is designed to be a concrete implementation of a circle within the Shape hierarchy.
     *
     * @note This class should not be instantiated directly. Instances should be created using the ShapeFactory or similar.
     * Derived classes should not be created.
     *
     * @see LDDrift::VecPos2D, LDDrift::VecCol, LDDrift::Angle, Shape
     */
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
        void Rotate(const Angle& angle) override;
        ~CircleShape() override;
    };
}

#endif
