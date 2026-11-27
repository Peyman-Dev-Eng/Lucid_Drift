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

#ifndef LUCID_DRIFT_LINE_H
#define LUCID_DRIFT_LINE_H
#include <VecPos2D.h>
#include <array>
#include <vector>
#include <VecCol.h>

namespace LDDrift::Actors
{
    /**
     * Line class represents a geometric line in a 2D space.
     *
     * @class Line
     * @brief A class for creating and manipulating a line defined by two points.
     *
     * This class encapsulates the functionality needed to create a line between two
     * points and provides methods to modify the line's endpoints and create
     * triangular representations of the line.
     *
     * @note The class assumes that the endpoints are provided as VecPos2D objects,
     * which are designed to handle only positive coordinates. Using non-positive
     * coordinates will result in the values being clamped to zero.
     *
     * @see VecPos2D
     */
    class Line final
    {
    public:
        struct PNT
        {
            LDDrift::VecPos2D Point_1;
            LDDrift::VecPos2D Point_2;
            LDDrift::VecPos2D Point_3;
        };

    public:
        Line();
        Line(const LDDrift::VecPos2D&, const LDDrift::VecPos2D&);
        void CreateTriangles();
        void SetFirstPoint(const LDDrift::VecPos2D&);
        void SetSecondPoint(const LDDrift::VecPos2D&);
        [[nodiscard]] float GetThickness() const;
        [[nodiscard]] LDDrift::VecPos2D GetFirstPoint() const;
        [[nodiscard]] LDDrift::VecPos2D GetSecondPoint() const;
        [[nodiscard]] const std::pmr::vector<PNT>& GetPoints() const;
        [[nodiscard]] const LDDrift::VecCol& GetColor() const;
        void SetLineColor(const LDDrift::VecCol& color);
        void SetThickness(float);
        void SetScreenSize(const LDDrift::VecPos2D&);
        ~Line();

    private:
        LDDrift::VecCol lineColor;
        std::pmr::vector<PNT> Points;
        LDDrift::VecPos2D FirstPoint;
        LDDrift::VecPos2D SecondPoint;
        int WidthScreen{500}, HeightScreen{500};
        float Thick{1};

    private: // functions
        [[nodiscard]] std::pmr::vector<PNT> Translate() const;
    };
}

#endif
