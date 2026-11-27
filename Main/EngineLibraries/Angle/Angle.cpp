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

#include "Angle.h"

LDDrift::Angle::Angle() = default;

LDDrift::Angle::Angle(const float ANGLE) {
    angle = ANGLE;
}

float LDDrift::Angle::GetAngleRadians() const {
    return static_cast<float>(angle * std::numbers::pi_v<float> / 180.0f);
}

float LDDrift::Angle::GetAngleRadians(const float ANGLE) {
    return static_cast<float>(ANGLE * std::numbers::pi_v<float> / 180.0);
}

LDDrift::Angle& LDDrift::Angle::operator=(const float ANGLE) {
    this->angle = ANGLE;
    return *this;
}

LDDrift::Angle& LDDrift::Angle::operator=(const Angle& angle_) {
    angle = angle_.angle;
    return *this;
}

LDDrift::Angle::~Angle() = default;
