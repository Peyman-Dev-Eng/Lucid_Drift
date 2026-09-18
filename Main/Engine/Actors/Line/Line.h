#ifndef LUCID_DRIFT_LINE_H
#define LUCID_DRIFT_LINE_H
#include <VecPos.h>
#include <array>
#include <vector>

namespace LDDrift::Actors
{
    class Line
    {
    private:
        struct PNT
        {
            LDDrift::VecPos2D Point_1;
            LDDrift::VecPos2D Point_2;
            LDDrift::VecPos2D Point_3;
        };
    private:
        std::vector<PNT> Points;
        LDDrift::VecPos2D FirstPoint;
        LDDrift::VecPos2D SecondPoint;
        float Thick{1};
    public:
        Line();
        Line(const LDDrift::VecPos2D&, const LDDrift::VecPos2D&);
        void CreateTriangles();
        void SetFirstPoint(const LDDrift::VecPos2D&);
        void SetSecondPoint(const LDDrift::VecPos2D&);
        [[nodiscard]] LDDrift::VecPos2D GetFirstPoint() const;
        [[nodiscard]] LDDrift::VecPos2D GetSecondPoint() const;
        ~Line();
    };
}

#endif
