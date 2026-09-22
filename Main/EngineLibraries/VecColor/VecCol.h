#ifndef LUCID_DRIFT_VECCOL_H
#define LUCID_DRIFT_VECCOL_H


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
        ~VecCol();
    };
}


#endif
