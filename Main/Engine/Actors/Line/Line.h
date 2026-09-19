#ifndef LUCID_DRIFT_LINE_H
#define LUCID_DRIFT_LINE_H
#include <VecPos.h>
#include <array>
#include <vector>

namespace LDDrift::Actors
{
    /**
     * Line class represents a geometric line in a 2D space.
     *
     * @class Line
     * @brief A class for creating and manipulating a line defined by two points.
     *
     * This class encapsulates the functionality needed to create a line between two
     * points and provides methods to modify the line's endpoints and create
     * triangular representations of the line.
     *
     * @note The class assumes that the endpoints are provided as VecPos2D objects,
     * which are designed to handle only positive coordinates. Using non-positive
     * coordinates will result in the values being clamped to zero.
     *
     * @see VecPos2D
     */
    class Line
    {
    public:
        struct PNT
        {
            LDDrift::VecPos2D Point_1;
            LDDrift::VecPos2D Point_2;
            LDDrift::VecPos2D Point_3;
        };

    public:
        Line();
        Line(const LDDrift::VecPos2D&, const LDDrift::VecPos2D&);
        Line& CreateTriangles();
        void SetFirstPoint(const LDDrift::VecPos2D&);
        void SetSecondPoint(const LDDrift::VecPos2D&);
        [[nodiscard]] LDDrift::VecPos2D GetFirstPoint() const;
        [[nodiscard]] LDDrift::VecPos2D GetSecondPoint() const;
        [[nodiscard]] std::vector<PNT> GetPoints() const;
        Line& SetThickness(float);
        Line& SetScreenSize(const LDDrift::VecPos2D&);
        ~Line();

    private:
        std::vector<PNT> Points;
        LDDrift::VecPos2D FirstPoint;
        LDDrift::VecPos2D SecondPoint;
        int WidthScreen{500}, HeightScreen{500};
        float Thick{1};

    private: // functions
        [[nodiscard]] std::vector<PNT> Translate() const;
    };
}

#endif
