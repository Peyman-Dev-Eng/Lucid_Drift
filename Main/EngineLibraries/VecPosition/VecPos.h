#ifndef LUCID_DRIFT_VECPOS_H
#define LUCID_DRIFT_VECPOS_H
#include <initializer_list>
#include <Assertions.h>
#include <cmath>

namespace LDDrift
{
    /**
     * VecPos2D class represents a two-dimensional vector with positive x and y coordinates.
     *
     * @class VecPos2D
     * @brief A simple vector class for handling 2D positions with positive values.
     *
     * This class provides basic operations for working with 2D vectors, ensuring that
     * both x and y coordinates remain positive. It is designed for scenarios where
     * only vectors with positive coordinates are valid or meaningful.
     *
     * @note All operations on this class maintain the positive constraint on coordinates.
     * Attempting to set or update a coordinate to a non-positive value will result in
     * the value being clamped to zero.
     *
     * @warning The use of non-positive coordinates is not supported and will lead
     * to unexpected behavior.
     *
     * @see Vec2D, VecNeg2D
     */
    class VecPos2D
    {
    private:
    public:
        float Y{};
        float X{};
        explicit VecPos2D();
        explicit VecPos2D(float x, float y);
        explicit VecPos2D(std::initializer_list<float> list);
        static VecPos2D Normalize(const VecPos2D& vec);
        static VecPos2D NormalLine(const VecPos2D& FirstVec, const VecPos2D& SecondVec);
        VecPos2D operator-(const VecPos2D& vec2) const;
        VecPos2D operator+(const VecPos2D& vec2) const;
        VecPos2D& operator-=(const VecPos2D& vec2);
        VecPos2D& operator+=(const VecPos2D& vec2);
        VecPos2D operator*(const VecPos2D& vec2) const;
        VecPos2D operator/(const VecPos2D& vec2) const;
        VecPos2D& operator*=(const VecPos2D& vec2);
        VecPos2D& operator/=(const VecPos2D& vec2);

        ~VecPos2D();
    };
}


#endif //LUCID_DRIFT_VECPOS_H
