// Copyright (C) 2026 Peyman
//
// This file is part of Lucid Drift.
// Lucid Drift is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// This software is distributed without any warranty.
// See the LICENSE file for the full license text.
// See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.

#ifndef LUCID_DRIFT_CIRCLE_SHAPE_H
#define LUCID_DRIFT_CIRCLE_SHAPE_H
#include "../MainShape/Shape.h"

namespace LDDrift::Actors
{
    /**
     * CircleShape class represents a geometric circle shape.
     *
     * @class Circle
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
    class Circle final : public LDDrift::Actors::Shape
    {
    private:
        float radiusNDC_X;
        float radiusNDC_Y;
        float radius;
        LDDrift::VecPos2D CenterPos;

    public:
        Circle();
        explicit Circle(const float& R);
        void SetRadius(const float& R);
        void SetCirclePosition(const LDDrift::VecPos2D& position);
        [[nodiscard]] const LDDrift::VecPos2D& GetCirclePosition() const;
        [[nodiscard]] float GetRadius() const;
        [[nodiscard]] LDDrift::VecCol CalculateAverageVertexColor() override;
        void Rebuild() override;
        void Rebuild(int width, int height) override;
        void Rotate(const Angle& angle) override;
        void Move(Dir direction) override;
        ~Circle() override;
    };
}

#endif
