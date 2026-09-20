#ifndef LUCID_DRIFT_SHAPE_H
#define LUCID_DRIFT_SHAPE_H
#include <vector>
#include <VecPos.h>
#include <VecCol.h>
#include <Angle.h>
#include <codecvt>

namespace LDDrift::Actors
{
    enum class Dir : uint
    {
        UP, DOWN,
        LEFT, RIGHT
    };

    /**
     * Shape class represents a geometric shape with various properties and operations.
     *
     * @class Shape
     * @brief A base class for representing and manipulating geometric shapes.
     *
     * This class provides a framework for defining and manipulating geometric shapes.
     * It includes properties such as points, colors, position, speed, and other attributes.
     * Shapes can be moved, rotated, and rebuilt.
     *
     * @note This is an abstract base class and should not be instantiated directly.
     * Derived classes should implement the Rebuild method to create the specific shape.
     *
     * @see LDDrift::VecPos2D, LDDrift::VecCol, LDDrift::Angle
     */
    class Shape
    {
    private:
        LDDrift::VecPos2D screenSize;
        LDDrift::VecPos2D OriginalPosition;
        std::vector<LDDrift::VecPos2D> Points;
        std::vector<LDDrift::VecCol> ColorOfPoints;
        uint PointCount;
        float Speed;
        bool FillShape;
        float Thickness;

    private: // private functions
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

    public:
        Shape();
        [[nodiscard]] const std::vector<VecPos2D>& GetPoints() const;
        void SetPointCount(uint point_count);
        [[nodiscard]] uint GetPointCount() const;
        void SetPoint(uint point_index, const LDDrift::VecPos2D& pos);
        [[nodiscard]] const LDDrift::VecPos2D& GetPoint(uint point_index) const;
        void Move(Dir direction);
        virtual void Rotate(const Angle& angle);
        void SetSpeed(float spd);
        void SetOriginalPosition(const LDDrift::VecPos2D& pos);
        [[nodiscard]] const LDDrift::VecPos2D& GetOriginalPosition() const;
        void SetPointColor(uint point_index, const LDDrift::VecCol& color);
        [[nodiscard]] const LDDrift::VecCol& GetPointColor(uint point_index) const;
        void ResetPointCount();
        void ResetPoints();
        void ResetColorOfPoints();
        void ResetOriginalPosition();
        void SetFillColor(bool IsFillShape);
        void SetThickness(float thickness);
        void SetScreenSize(const LDDrift::VecPos2D& size);
        void SetPosition(const LDDrift::VecPos2D& pos);
        [[nodiscard]] bool IsFillShape() const;
        [[nodiscard]] float GetThickness() const;
        [[nodiscard]] std::vector<LDDrift::VecPos2D> TransformPoints() const;
        virtual void Rebuild() = 0;
        virtual ~Shape();

    protected:
        [[nodiscard]] const LDDrift::VecPos2D& GetScreenSize() const;
    };
}

#endif
