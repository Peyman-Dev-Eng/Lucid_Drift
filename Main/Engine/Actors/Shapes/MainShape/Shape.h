#ifndef LUCID_DRIFT_SHAPE_H
#define LUCID_DRIFT_SHAPE_H
#include <vector>
#include <VecPos.h>
#include <VecCol.h>
#include <Angle.h>

namespace LDDrift::Actors
{
    enum class Dir : uint
    {
        UP, DOWN,
        LEFT, RIGHT
    };

    class Shape
    {
    private:
        std::vector<LDDrift::VecPos2D> points;
        std::vector<LDDrift::VecCol> ColorOfPoints;
        uint PointCount = 0;
        float Speed = 0.01;

    private: // private functions
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

    public:
        Shape();
        void SetPointCount(uint point_count);
        uint GetPointCount();
        void SetPoint(uint point_index, LDDrift::VecPos2D pos);
        LDDrift::VecPos2D GetPoint(uint point_index);
        void Move(Dir direction);
        void Rotate(const Angle& angle);
        void SetSpeed(float spd);
        void SetPointColor(uint point_index, LDDrift::VecCol color);
        LDDrift::VecCol GetPointColor(uint point_index);
        virtual ~Shape();
    };
}

#endif
