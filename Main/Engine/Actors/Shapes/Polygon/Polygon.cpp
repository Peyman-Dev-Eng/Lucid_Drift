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

#include "Polygon.h"

LDDrift::Actors::Polygon::Polygon() = default;

LDDrift::VecCol LDDrift::Actors::Polygon::CalculateAverageVertexColor() {
    CTM_assert(ShapeIsConvex(), "this is shape is not a convex polygon");
    LDDrift::VecCol resultColor;
    const std::pmr::vector<LDDrift::VecCol>& verticesColor = this->GetColorOfPoints();
    const std::size_t pointCount = this->GetPointCount();
    for (std::size_t point = 0; point < this->GetPointCount(); ++point) {
        resultColor += verticesColor[point];
    }
    resultColor /= static_cast<float>(pointCount);
    return resultColor;
}

void LDDrift::Actors::Polygon::Rebuild() {
    this->SetOriginalPositionToCenter();
}

void LDDrift::Actors::Polygon::Rebuild(const int width, const int height) {
    this->SetScreenSize({static_cast<float>(width), static_cast<float>(height)});

}

void LDDrift::Actors::Polygon::Move(const Dir direction) {
    if (direction == Dir::UP) {
        this->MoveUp();
        return;
    } else if (direction == Dir::DOWN) {
        this->MoveDown();
        return;
    } else if (direction == Dir::LEFT) {
        this->MoveLeft();
        return;
    } else if (direction == Dir::RIGHT) {
        this->MoveRight();
        return;
    }
}

LDDrift::Actors::Polygon::~Polygon() = default;
