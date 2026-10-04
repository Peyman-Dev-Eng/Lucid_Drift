#ifndef LUCID_DRIFT_SHAPE_H
#define LUCID_DRIFT_SHAPE_H
#include <vector>
#include <VecPos.h>
#include <VecCol.h>
#include <Angle.h>
#include <codecvt>
#include <ShapeData.h>
#include <SubSystems/Transform/Transform.h>

namespace LDDrift::ActorType
{
    class convex {};

    class concave {};
}

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
        struct isConvexData
        {
            bool isConvex;
            int pointDirection;
        };

    private:
        LDDrift::VecPos2D screenSize;
        LDDrift::VecPos2D OriginalPosition;
        std::vector<LDDrift::VecPos2D> Points;
        std::vector<LDDrift::VecCol> ColorOfPoints;
        uint PointCount;
        float Speed;
        float SpeedNDC_X;
        float SpeedNDC_Y;
        bool FillShape;
        float Thickness;
        bool HaveThickness;

    protected: // private functions
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

    public:
        Shape();
        [[nodiscard]] std::vector<VecPos2D> GetGlobalPoints() const;
        [[nodiscard]] const std::vector<LDDrift::VecPos2D>& GetNDC_Points() const;
        void SetPointCount(std::size_t point_count);
        [[nodiscard]] std::size_t GetPointCount() const;
        void SetPoint(std::size_t point_index, const LDDrift::VecPos2D& pos);
        [[nodiscard]] LDDrift::VecPos2D GetGlobalPoint(std::size_t point_index) const;
        [[nodiscard]] const LDDrift::VecPos2D& GetNDC_Point(std::size_t point_index) const;
        [[nodiscard]] float GetSpeed() const;
        [[nodiscard]] float GetSpeedNDC_X() const;
        [[nodiscard]] float GetSpeedNDC_Y() const;
        virtual void Move(Dir direction);
        virtual void Rotate(const Angle& angle);
        void SetSpeed(float spd);
        void SetOriginalPosition(const LDDrift::VecPos2D& pos);
        [[nodiscard]] const LDDrift::VecPos2D& GetOriginalPosition() const;
        void SetPointColor(uint point_index, const LDDrift::VecCol& color);
        [[nodiscard]] const LDDrift::VecCol& GetPointColor(std::size_t point_index) const;
        [[nodiscard]] const std::vector<LDDrift::VecCol>& GetColorOfPoints() const;
        void ResetPointCount();
        void ResetPoints();
        void ResetColorOfPoints();
        void ResetOriginalPosition();
        void SetFillColor(bool IsFillShape);
        void SetThickness(float thickness);
        void SetScreenSize(const LDDrift::VecPos2D& size);
        void SetAllPointsColor(const LDDrift::VecCol& targetColor);
        [[nodiscard]] bool IsFillShape() const;
        [[nodiscard]] bool IsHaveThickness() const;
        [[nodiscard]] float GetThickness() const;
        [[nodiscard]] std::vector<LDDrift::VecPos2D> TransformPoints() const;
        [[nodiscard]] virtual LDDrift::VecCol CalculateAverageVertexColor() const = 0;
        [[nodiscard]] LDDrift::VecPos2D CalculateAveragePointPosition() const;
        virtual void Rebuild() = 0;
        virtual void Rebuild(int width, int height) = 0;
        virtual ~Shape();
        [[nodiscard]] isConvexData ShapeIsConvex() const;

    protected:
        [[nodiscard]] const LDDrift::VecPos2D& GetScreenSize() const;
    };
}

#endif
