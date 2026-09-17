#include "Angle.h"

LDDrift::Angle::Angle() = default;

float LDDrift::Angle::GetAngleRadians(const float angle) {
    return static_cast<float>(angle * std::numbers::pi_v<float> / 180.0);
}

LDDrift::Angle::~Angle() = default;

