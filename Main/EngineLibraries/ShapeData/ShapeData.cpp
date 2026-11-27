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

#include "ShapeData.h"

LDDrift::ShapeData::ShapeData() = default;

LDDrift::ShapeData::ShapeData(const std::pmr::vector<LDDrift::VecPos2D>& vertices,
                              const std::pmr::vector<LDDrift::VecCol>& points_colors) {
    std::size_t vertexIndex = 0;
    this->Vertices.reserve(vertices.size());
    for (const LDDrift::VecPos2D& vertex : vertices) {
        this->Vertices[vertexIndex].x = vertex.X;
        this->Vertices[vertexIndex].y = vertex.Y;
        this->Vertices[vertexIndex].z = 0.0f;
        ++vertexIndex;
    }
    std::size_t colorIndex = 0;
    this->PointsColors.reserve(points_colors.size());
    for (const LDDrift::VecCol& color : points_colors) {
        this->PointsColors[colorIndex].R = color.R;
        this->PointsColors[colorIndex].G = color.G;
        this->PointsColors[colorIndex].B = color.B;
        this->PointsColors[colorIndex].A = color.A;
        ++colorIndex;
    }
}

LDDrift::ShapeData::~ShapeData() = default;
