// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

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
