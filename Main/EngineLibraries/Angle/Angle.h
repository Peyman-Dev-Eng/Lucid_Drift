#ifndef LUCID_DRIFT_AGNLE_H
#define LUCID_DRIFT_AGNLE_H
#include <cmath>
#include <numbers>

namespace LDDrift
{
    class Angle
    {
    public:
        Angle();
        static float GetAngleRadians(float angle);
        ~Angle();
    };
}

#endif
