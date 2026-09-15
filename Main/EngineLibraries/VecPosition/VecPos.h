#ifndef LUCID_DRIFT_VECPOS_H
#define LUCID_DRIFT_VECPOS_H
#include <initializer_list>
#include <Assertions.h>

/**
 * Represents a 2D vector with integer coordinates.
 *
 * Provides methods for basic vector operations.
 *
 * @class VecPos2D
 */
class VecPos2D
{
public:
    double Y{};
    double X{};
    explicit VecPos2D();
    explicit VecPos2D(double x, double y);
    explicit VecPos2D(std::initializer_list<double> list);
    VecPos2D operator-(const VecPos2D& vec2) const;
    VecPos2D operator+(const VecPos2D& vec2) const;
    VecPos2D operator-=(const VecPos2D& vec2) const;
    VecPos2D operator+=(const VecPos2D& vec2) const;
    VecPos2D operator*(const VecPos2D& vec2) const;
    VecPos2D operator/(const VecPos2D& vec2) const;
    VecPos2D operator*=(const VecPos2D& vec2) const;
    VecPos2D operator/=(const VecPos2D& vec2) const;

    ~VecPos2D();
};


#endif //LUCID_DRIFT_VECPOS_H
