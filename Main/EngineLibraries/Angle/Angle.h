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
        Angle& operator= (float ANGLE);
        Angle& operator= (const Angle& angle);
        ~Angle();
    };
}

#endif
