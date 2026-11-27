
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

#include "VecPos3D.h"

LDDrift::VecPos3D::VecPos3D() = default;

LDDrift::VecPos3D::VecPos3D(
    const float x,
    const float y,
    const float z)
{
    X = x;
    Y = y;
    Z = z;
}

LDDrift::VecPos3D::VecPos3D(
    const std::initializer_list<float> list)
{
    GLB_assert(list.size() == 3);

    auto it = list.begin();

    X = *it++;
    Y = *it++;
    Z = *it;
}

LDDrift::VecPos3D LDDrift::VecPos3D::Normalize(
    const VecPos3D& vec)
{
    const float length = std::sqrt(
        vec.X * vec.X +
        vec.Y * vec.Y +
        vec.Z * vec.Z
    );

    if (length == 0.0f)
        return VecPos3D{0.0f, 0.0f, 0.0f};

    return VecPos3D{
        vec.X / length,
        vec.Y / length,
        vec.Z / length
    };
}

// Dot Product
float LDDrift::VecPos3D::Dot(
    const VecPos3D& a,
    const VecPos3D& b)
{
    return
        a.X * b.X +
        a.Y * b.Y +
        a.Z * b.Z;
}

// Cross Product
LDDrift::VecPos3D LDDrift::VecPos3D::Cross(
    const VecPos3D& a,
    const VecPos3D& b)
{
    return VecPos3D{
        a.Y * b.Z - a.Z * b.Y,
        a.Z * b.X - a.X * b.Z,
        a.X * b.Y - a.Y * b.X
    };
}

// Angle Between
float LDDrift::VecPos3D::AngleBetween(
    const VecPos3D& origin,
    const VecPos3D& a,
    const VecPos3D& b)
{
    const VecPos3D va = a - origin;
    const VecPos3D vb = b - origin;

    const float lenA = std::sqrt(Dot(va, va));
    const float lenB = std::sqrt(Dot(vb, vb));

    if (lenA == 0.0f || lenB == 0.0f)
        return 0.0f;

    const float cosine = std::clamp(
        Dot(va, vb) / (lenA * lenB),
        -1.0f,
        1.0f
    );

    return std::acos(cosine) *
           180.0f / std::acos(-1.0f);
}

// Addition
LDDrift::VecPos3D LDDrift::VecPos3D::operator+(
    const VecPos3D& vec) const
{
    return VecPos3D{
        X + vec.X,
        Y + vec.Y,
        Z + vec.Z
    };
}

LDDrift::VecPos3D LDDrift::VecPos3D::operator+(
    const float& value) const
{
    return VecPos3D{
        X + value,
        Y + value,
        Z + value
    };
}

// Subtraction
LDDrift::VecPos3D LDDrift::VecPos3D::operator-(
    const VecPos3D& vec) const
{
    return VecPos3D{
        X - vec.X,
        Y - vec.Y,
        Z - vec.Z
    };
}

LDDrift::VecPos3D LDDrift::VecPos3D::operator-(
    const float& value) const
{
    return VecPos3D{
        X - value,
        Y - value,
        Z - value
    };
}

// Addition assignment
LDDrift::VecPos3D& LDDrift::VecPos3D::operator+=(
    const VecPos3D& vec)
{
    X += vec.X;
    Y += vec.Y;
    Z += vec.Z;

    return *this;
}

LDDrift::VecPos3D& LDDrift::VecPos3D::operator+=(
    const float& value)
{
    X += value;
    Y += value;
    Z += value;

    return *this;
}

// Subtraction assignment
LDDrift::VecPos3D& LDDrift::VecPos3D::operator-=(
    const VecPos3D& vec)
{
    X -= vec.X;
    Y -= vec.Y;
    Z -= vec.Z;

    return *this;
}

LDDrift::VecPos3D& LDDrift::VecPos3D::operator-=(
    const float& value)
{
    X -= value;
    Y -= value;
    Z -= value;

    return *this;
}

// Multiplication
LDDrift::VecPos3D LDDrift::VecPos3D::operator*(
    const VecPos3D& vec) const
{
    return VecPos3D{
        X * vec.X,
        Y * vec.Y,
        Z * vec.Z
    };
}

LDDrift::VecPos3D LDDrift::VecPos3D::operator*(
    const float& value) const
{
    return VecPos3D{
        X * value,
        Y * value,
        Z * value
    };
}

// Division
LDDrift::VecPos3D LDDrift::VecPos3D::operator/(
    const VecPos3D& vec) const
{
    return VecPos3D{
        X / vec.X,
        Y / vec.Y,
        Z / vec.Z
    };
}

LDDrift::VecPos3D LDDrift::VecPos3D::operator/(
    const float& value) const
{
    return VecPos3D{
        X / value,
        Y / value,
        Z / value
    };
}

// Multiplication assignment
LDDrift::VecPos3D& LDDrift::VecPos3D::operator*=(
    const VecPos3D& vec)
{
    X *= vec.X;
    Y *= vec.Y;
    Z *= vec.Z;

    return *this;
}

LDDrift::VecPos3D& LDDrift::VecPos3D::operator*=(
    const float& value)
{
    X *= value;
    Y *= value;
    Z *= value;

    return *this;
}

// Division assignment
LDDrift::VecPos3D& LDDrift::VecPos3D::operator/=(
    const VecPos3D& vec)
{
    X /= vec.X;
    Y /= vec.Y;
    Z /= vec.Z;

    return *this;
}

LDDrift::VecPos3D& LDDrift::VecPos3D::operator/=(
    const float& value)
{
    X /= value;
    Y /= value;
    Z /= value;

    return *this;
}

// Comparison
bool LDDrift::VecPos3D::operator==(
    const VecPos3D& vec) const
{
    return X == vec.X &&
           Y == vec.Y &&
           Z == vec.Z;
}

bool LDDrift::VecPos3D::operator!=(
    const VecPos3D& vec) const
{
    return !(*this == vec);
}

LDDrift::VecPos3D::~VecPos3D() = default;
