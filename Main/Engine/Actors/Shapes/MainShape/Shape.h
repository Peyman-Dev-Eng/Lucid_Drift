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
        LDDrift::VecPos2D OriginalPosition;
        std::vector<LDDrift::VecPos2D> Points;
        std::vector<LDDrift::VecCol> ColorOfPoints;
        uint PointCount;
        float Speed;

    private: // private functions
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

    public:
        Shape();
        [[nodiscard]] std::vector<VecPos2D> GetPoints() const;
        void SetPointCount(uint point_count);
        [[nodiscard]] uint GetPointCount() const;
        void SetPoint(uint point_index, const LDDrift::VecPos2D& pos);
        LDDrift::VecPos2D GetPoint(uint point_index);
        void Move(Dir direction);
        void Rotate(const Angle& angle);
        void SetSpeed(float spd);
        void SetOriginalPosition(const LDDrift::VecPos2D& pos);
        [[nodiscard]] LDDrift::VecPos2D GetOriginalPosition() const;
        void SetPointColor(uint point_index, const LDDrift::VecCol& color);
        LDDrift::VecCol GetPointColor(uint point_index);
        void ResetPointCount();
        void ResetPoints();
        void ResetColorOfPoints();
        void ResetOriginalPosition();
        void SetPosition(const LDDrift::VecPos2D& pos);
        virtual void Rebuild() = 0;
        virtual ~Shape() = 0;
    };
}

#endif
