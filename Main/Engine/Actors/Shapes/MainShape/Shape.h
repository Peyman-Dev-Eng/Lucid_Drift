#ifndef LUCID_DRIFT_SHAPE_H
#define LUCID_DRIFT_SHAPE_H
#include <vector>
#include <VecPos.h>
namespace LDDrift::Actors::Shapes
{
    enum class Dir : uint
    {
        UP, DOWN,
        LEFT, RIGHT
    };

    class Shape
    {
    private:
        std::vector<LDDrift::VecPosition::VecPos2D> points;
        uint PointCount = 0;

    private: // private functions
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

    public:
        Shape();
        void SetPointCount(uint point_count);
        uint GetPointCount();
        void SetPoint(uint point_index, LDDrift::VecPosition::VecPos2D pos);
        LDDrift::VecPosition::VecPos2D GetPoint(uint point_index);
        void Move(Dir direction);
        void Rotate(float);
        virtual ~Shape();
    };
}

#endif
