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
#ifndef LUCID_DRIFT_VECTOR_COL_H
#define LUCID_DRIFT_VECTOR_COL_H
#include <algorithm>


namespace LDDrift
{
    /**
     * VecCol class represents a color in RGBA format.
     *
     * @class VecCol
     * @brief A simple color class for handling RGBA colors.
     *
     * This class provides basic operations for working with RGBA colors. It allows
     * setting and retrieving the red, green, blue, and alpha components of a color.
     * Additionally, it provides predefined methods for setting common colors such as red,
     * green, blue, yellow, orange, purple, white, and black.
     *
     * @note The alpha component determines the transparency of the color. A value of 1.0 is fully opaque,
     * while a value of 0.0 is fully transparent.
     *
     * @see VecPos2D, Angle, Shape
     */
    class VecCol final
    {
    public:
        float R{}, G{}, B{}, A{};
        VecCol();
        VecCol(float red, float green, float blue, float alpha);
        void Red();
        void Green();
        void Blue();
        void Yellow();
        void Orange();
        void Purple();
        void White();
        void Black();
        void SetColor(const float& red, const float& green, const float& blue, const float& alpha);
        VecCol& operator+=(const VecCol& vec);
        VecCol& operator-=(const VecCol& vec);
        VecCol& operator*=(const VecCol& vec);
        VecCol& operator/=(const VecCol& vec);
        VecCol operator-(const VecCol& vec) const;
        VecCol operator+(const VecCol& vec) const;
        VecCol operator*(const VecCol& vec) const;
        VecCol operator/(const VecCol& vec) const;
        VecCol& operator-=(const float& color);
        VecCol& operator+=(const float& color);
        VecCol& operator*=(const float& color);
        VecCol& operator/=(const float& color);
        VecCol operator-(const float& color) const;
        VecCol operator*(const float& color) const;
        VecCol operator/(const float& color) const;
        VecCol operator+(const float& color) const;
        bool operator==(const VecCol& vec) const;
        bool operator!=(const VecCol& vec) const;
        ~VecCol();
    };
}


#endif
