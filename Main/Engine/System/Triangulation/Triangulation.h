#ifndef LUCID_DRIFT_TRIANGLE_H
#define LUCID_DRIFT_TRIANGLE_H
#define UPPER_BOUND 100
#include <vector>
#include <algorithm>
#include <Actors/Shapes/MainShape/Shape.h>
#include <SubSystems/PointHitTesting/PointHitTesting.h>

namespace LDDrift
{
    template <typename ShapeType>
    class Triangulation final
    {
    private:
        LDDrift::Actors::Shape* shape;

    private: // functions
        void TrianglesForConcaveShape(std::vector<float>& vertices) const {
            const std::size_t shapePointNumber = shape->GetPointCount();
            std::vector<std::size_t> targetNumberOfPoints;
            for (std::size_t point = 0; point < shapePointNumber; ++point) {
                targetNumberOfPoints.push_back(point);
            }
            std::size_t counter = 0;
            while (targetNumberOfPoints.size() != 3 && counter != UPPER_BOUND) {
                constexpr std::size_t pointNumber = 0;
                const LDDrift::VecPos2D& pointA = shape->GetNDC_Point(targetNumberOfPoints[pointNumber]);
                const LDDrift::VecPos2D& pointB = shape->GetNDC_Point(targetNumberOfPoints[pointNumber + 1]);
                const LDDrift::VecPos2D& pointC = shape->GetNDC_Point(targetNumberOfPoints[pointNumber + 2]);
                const float cross =
                    (pointB.X - pointA.X) * (pointC.Y - pointB.Y)
                    - (pointB.Y - pointA.Y) * (pointC.X - pointA.X);
                if (const bool isConvexCorner = cross * shape->ShapeIsConvex().pointDirection > 0.0f; !isConvexCorner) {
                    continue;
                }
                bool notFoundPointInTriangle = true;
                for (std::size_t point = 0; point < shapePointNumber; ++point) {
                    if (point == pointNumber || point == (pointNumber + 1) % shapePointNumber ||
                        point == (pointNumber + 2) % shapePointNumber) { // رد کردن نقطه هایی که با انها مثلث ساختیم
                        continue;
                    }
                    if (LDDrift::PointHitTesting::pointHitTesting(shape->GetNDC_Point(point),
                                                                  std::vector<LDDrift::VecPos2D>{
                                                                      pointA, pointB, pointC
                                                                  })) {
                        notFoundPointInTriangle = false;
                        break;
                    }
                }
                if (notFoundPointInTriangle) {
                    vertices.push_back(pointA.X);
                    vertices.push_back(pointA.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(pointB.X);
                    vertices.push_back(pointB.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(pointC.X);
                    vertices.push_back(pointC.Y);
                    vertices.push_back(0.0f);
                    targetNumberOfPoints.erase(targetNumberOfPoints.begin() + 1);
                }
                ++counter;
            }
            vertices.push_back(shape->GetNDC_Point(targetNumberOfPoints[0]).X);
            vertices.push_back(shape->GetNDC_Point(targetNumberOfPoints[0]).Y);
            vertices.push_back(0.0f);
            vertices.push_back(shape->GetNDC_Point(targetNumberOfPoints[1]).X);
            vertices.push_back(shape->GetNDC_Point(targetNumberOfPoints[1]).Y);
            vertices.push_back(0.0f);
            vertices.push_back(shape->GetNDC_Point(targetNumberOfPoints[2]).X);
            vertices.push_back(shape->GetNDC_Point(targetNumberOfPoints[2]).Y);
            vertices.push_back(0.0f);
        }

        void TrianglesForConvexShape(std::vector<float>& vertices) const {
            // get center point position of shape
            LDDrift::VecPos2D CenterPos{0, 0};
            const std::size_t shapePointNumber = shape->GetPointCount();
            for (std::size_t pointNumber = 0; pointNumber < shapePointNumber; ++pointNumber) {
                CenterPos += shape->GetNDC_Point(pointNumber);
            }
            CenterPos /= shapePointNumber;
            /////////////////////////////////////////////
            // create triangles
            for (std::size_t pointNumber = 0; pointNumber < shapePointNumber; ++pointNumber) {
                const std::size_t currentPoint = pointNumber;
                const std::size_t nextPoint = pointNumber == shapePointNumber - 1 ? 0 : pointNumber + 1;
                vertices.push_back(CenterPos.X);
                vertices.push_back(CenterPos.Y);
                vertices.push_back(0.0f);
                vertices.push_back(shape->GetNDC_Point(currentPoint).X);
                vertices.push_back(shape->GetNDC_Point(currentPoint).Y);
                vertices.push_back(0.0f);
                vertices.push_back(shape->GetNDC_Point(nextPoint).X);
                vertices.push_back(shape->GetNDC_Point(nextPoint).Y);
                vertices.push_back(0.0f);
            }
        }

    public:
        Triangulation() {
            shape = nullptr;
        }

        explicit Triangulation(LDDrift::Actors::Shape* shapePTR = nullptr) : shape(nullptr) {
            this->SetShapeTarget(shapePTR);
        }

        void SetShapeTarget(LDDrift::Actors::Shape* shapePTR) {
            NPV_assert(shapePTR != nullptr);
            shape = shapePTR;
        }

        [[nodiscard]] std::vector<float> CreateTriangles() const {
            if (const std::size_t pointNumber = shape->GetPointCount(); pointNumber <= 3) {
                std::cerr <<
                    R"( The shape you are attempting to convert into a triangle is either already a triangle,
                        or its number of vertices is invalid.
                        Therefore, be mindful of the valid data you extract from this function.)" << std::endl;
                return std::vector<float>{0.0f};
            }
            if constexpr (std::is_same_v<ShapeType, LDDrift::ActorType::convex>) {
                std::vector<float> vertices;
                this->TrianglesForConvexShape(vertices);
                return vertices;
            } else if constexpr (std::is_same_v<ShapeType, LDDrift::ActorType::concave>) {
                std::vector<float> vertices;
                this->TrianglesForConcaveShape(vertices);
                return vertices;
            } else {
                std::cerr << RED <<
                    R"( You did not submit a valid type for constructing a triangle on the shape.
                        You can choose between two categories of shapes: convex or concave.)";
                return std::vector<float>{0.0f};
            }
        }

        ~Triangulation() = default;
    };
}

#endif
