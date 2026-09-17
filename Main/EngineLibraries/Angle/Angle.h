#ifndef LUCID_DRIFT_AGNLE_H
#define LUCID_DRIFT_AGNLE_H
#include <cmath>
#include <numbers>

namespace LDDrift
{
    class Angle
    {
    private:
        float angle{};
    public:
        Angle();
        Angle(float ANGLE);
        float GetAngleRadians() const;
        static float GetAngleRadians(float ANGLE);
        ~Angle();
    };
}

#endif
