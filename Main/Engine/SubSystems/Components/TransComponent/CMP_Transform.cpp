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

#include "CMP_Transform.h"

LDDrift::CMP_Transform::CMP_Transform() = default;

LDDrift::CMP_Transform::~CMP_Transform() = default;

void LDDrift::CMP_Transform::SetRotation(const LDDrift::Angle& Rotation_) {
    rotation = Rotation_;
}

void LDDrift::CMP_Transform::SetScale(const Scale& Scale_) {
    scale = Scale_;
}

void LDDrift::CMP_Transform::SetPoints(const std::pmr::vector<LDDrift::VecPos2D>& Points_) {
    points = Points_;
}

void LDDrift::CMP_Transform::SetTranslation(const LDDrift::VecPos2D& Translation_) {
    translation = Translation_;
}

void LDDrift::CMP_Transform::Calculate() {
    // calculate center point position for shape
    LDDrift::VecPos2D center{0, 0};
    for (const auto& point : points) {
        center += point;
    }
    center /= static_cast<float>(points.size());
    // use scale
    for (LDDrift::VecPos2D& point : points) {
        point.X = center.X + (point.X - center.X) * scale.x;
        point.Y = center.Y + (point.Y - center.Y) * scale.y;
    }
    // use rotation
    const float rad = rotation.GetAngleRadians();
    const float sinRad = std::sin(rad);
    const float cosRad = std::cos(rad);
    for (LDDrift::VecPos2D& point : points) {
        const float Base_X_Value = point.X - center.X;
        const float Base_Y_Value = point.Y - center.Y;
        point.X = Base_X_Value * cosRad - Base_Y_Value * sinRad;
        point.Y = Base_X_Value * sinRad + Base_Y_Value * cosRad;
        point.X += center.X;
        point.Y += center.Y;
    }
    if (translation.X == 0 && translation.Y == 0) {
        return;
    }
    for (LDDrift::VecPos2D& point : points) {
        point += translation;
    }
}
