/*
* Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */
#ifndef LUCID_DRIFT_SHAPEDATA_H
#define LUCID_DRIFT_SHAPEDATA_H
#include <vector>
#include <VecCol.h>
#include <VecPos2D.h>

namespace LDDrift
{
    enum class JoinLineType : long long int
    {
        Miter = 2147483647,
        Round = 4294967291,
        Bevel = 9999999967,
        Null = -1
    };

    class ShapeData
    {
    private:
        struct Vertex
        {
            float x, y, z;
        };

    public:
        std::pmr::vector<Vertex> Vertices;
        std::pmr::vector<VecCol> PointsColors;
        ShapeData();
        ShapeData(const std::pmr::vector<LDDrift::VecPos2D>& vertices, const std::pmr::vector<LDDrift::VecCol>& points_colors);
        ~ShapeData();
    };
}

#endif
