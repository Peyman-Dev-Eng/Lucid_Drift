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

#include "CMP_Collider.h"

LDDrift::CMP_Collider::CMP_Collider() {
    BoundingBox.reserve(4);
    normals.reserve(3);
}

LDDrift::CMP_Collider::~CMP_Collider() = default;

void LDDrift::CMP_Collider::Load(const std::pmr::vector<LDDrift::VecPos2D>& vertices) {
    CTM_assert(vertices.size() != 0, "vertices is empty")
    if (Loaded)
        unLoad();
    // set normals
    const std::size_t pointCount = vertices.size();
    float min_X_position = vertices[0].X, min_Y_position = vertices[0].Y;
    float max_X_position = vertices[pointCount - 1].X, max_Y_position = vertices[pointCount - 1].Y;
    normals.reserve(pointCount);
    for (std::size_t c_point_index = 0; c_point_index < pointCount; ++c_point_index) {
        const std::size_t p_point_index = c_point_index == 0 ? pointCount - 1 : c_point_index - 1;
        normals.push_back(LDDrift::VecPos2D::NormalLine(vertices[c_point_index], vertices[p_point_index]));
    }

    for (std::size_t c = 1; c < pointCount; ++c) {
        min_X_position = std::min(min_X_position, vertices[c].X);
        max_X_position = std::max(max_X_position, vertices[c].X);

        min_Y_position = std::min(min_Y_position, vertices[c].Y);
        max_Y_position = std::max(max_Y_position, vertices[c].Y);
    }

    BoundingBox.reserve(4);

    BoundingBox.push_back(LDDrift::VecPos2D{min_X_position - 20, max_Y_position + 20});
    BoundingBox.push_back(LDDrift::VecPos2D{max_X_position + 20, max_Y_position + 20});
    BoundingBox.push_back(LDDrift::VecPos2D{max_X_position + 20, min_Y_position - 20});
    BoundingBox.push_back(LDDrift::VecPos2D{min_X_position - 20, min_Y_position - 20});
    Loaded = true;
}

void LDDrift::CMP_Collider::unLoad() {
    BoundingBox.clear();
    normals.clear();
    Loaded = false;
}

void LDDrift::CMP_Collider::SetActive(const bool active_) {
    Active = active_;
}
