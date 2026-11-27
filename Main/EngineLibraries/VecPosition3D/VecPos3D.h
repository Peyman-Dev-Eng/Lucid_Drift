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

#ifndef LUCID_DRIFT_VECTOR_POSITION_3D_H
#define LUCID_DRIFT_VECTOR_POSITION_3D_H

#include <Assertions.h>
#include <cmath>
#include <initializer_list>
#include <algorithm>
#include <ostream>

namespace LDDrift
{

    class VecPos3D
    {
    public:
        float Y{};
        float X{};
        float Z{};

        explicit VecPos3D();
        VecPos3D(float x, float y, float z);
        VecPos3D(std::initializer_list<float> list);

        static VecPos3D Normalize(const VecPos3D& vec);

        // Vector operations
        static float Dot(const VecPos3D& a, const VecPos3D& b);
        static VecPos3D Cross(const VecPos3D& a, const VecPos3D& b);

        static float AngleBetween(
            const VecPos3D& origin,
            const VecPos3D& a,
            const VecPos3D& b
        );

        // Arithmetic operators
        VecPos3D operator-(const VecPos3D& vec) const;
        VecPos3D operator-(const float& value) const;

        VecPos3D operator+(const VecPos3D& vec) const;
        VecPos3D operator+(const float& value) const;

        VecPos3D& operator-=(const VecPos3D& vec);
        VecPos3D& operator-=(const float& value);

        VecPos3D& operator+=(const VecPos3D& vec);
        VecPos3D& operator+=(const float& value);

        VecPos3D operator*(const VecPos3D& vec) const;
        VecPos3D operator*(const float& value) const;

        VecPos3D operator/(const VecPos3D& vec) const;
        VecPos3D operator/(const float& value) const;

        VecPos3D& operator*=(const VecPos3D& vec);
        VecPos3D& operator*=(const float& value);

        VecPos3D& operator/=(const VecPos3D& vec);
        VecPos3D& operator/=(const float& value);

        // Comparison operators
        bool operator==(const VecPos3D& vec) const;
        bool operator!=(const VecPos3D& vec) const;

        ~VecPos3D();
    };
}

// Stream operator
inline std::ostream& operator<<(
    std::ostream& stream,
    const LDDrift::VecPos3D& vec)
{
    stream << "X: " << vec.X
           << " - Y: " << vec.Y
           << " - Z: " << vec.Z;

    return stream;
}

// Scalar multiplication
inline LDDrift::VecPos3D operator*(
    const float& value,
    const LDDrift::VecPos3D& vec)
{
    return vec * value;
}

#endif
