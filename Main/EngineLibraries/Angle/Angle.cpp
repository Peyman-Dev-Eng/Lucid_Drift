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

LDDrift::Angle::~Angle() = default;

