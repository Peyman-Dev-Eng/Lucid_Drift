#ifndef LUCID_DRIFT_AGNLE_H
#define LUCID_DRIFT_AGNLE_H
#include <cmath>
#include <numbers>

namespace LDDrift
{
    class Angle
    {
    private:
    public:
        float angle{};
        Angle();
        Angle(float ANGLE);
        [[nodiscard]] float GetAngleRadians() const;
        static float GetAngleRadians(float ANGLE);
        ~Angle();
    };
}

#endif
