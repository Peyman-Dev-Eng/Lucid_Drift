#ifndef LUCID_DRIFT_AGNLE_H
#define LUCID_DRIFT_AGNLE_H
#include <cmath>
#include <numbers>

namespace LDDrift
{
    /**
     * @class Angle
     * @brief Represents an angle in degrees and provides methods to convert it to radians.
     *
     * The Angle class is used to store an angle value in degrees. It provides methods to retrieve the angle
     * in radians and to create an Angle object from a degree value.
     *
     * @note This class is primarily used for angle-related calculations, where angles are often needed
     * in radians for trigonometric functions.
     *
     * @see Shape, VecPos2D
     */
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
