#ifndef LUCID_DRIFT_TRIANGLE_H
#define LUCID_DRIFT_TRIANGLE_H
#define UPPER_BOUND 100
#include <vector>
#include <algorithm>
#include <numbers>
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

        static float Cross(const VecPos2D& a, const VecPos2D& b, const VecPos2D& c) {
            return (b.X - a.X) * (c.Y - a.Y) -
                (b.Y - a.Y) * (c.X - a.X);
        }

        void TrianglesForThickShapes(std::vector<float>& vertices) const {
            const std::vector<LDDrift::VecPos2D>& points = shape->GetGlobalPoints();

            const std::size_t pointCountOfShape = points.size();
            const float halfThick = shape->GetThickness() / 2;
            for (std::size_t point = 0; point < pointCountOfShape; ++point) {
                const std::size_t previousPoint = (point + pointCountOfShape - 1) % pointCountOfShape;
                const std::size_t currentPoint = point;
                const std::size_t nextPoint = (point + 1) % pointCountOfShape;

                LDDrift::Actors::Line line(points[currentPoint], points[nextPoint]);
                line.SetThickness(halfThick * 2);
                line.SetScreenSize(shape->GetScreenSize());
                line.CreateTriangles();

                const std::vector<LDDrift::Actors::Line::PNT>& pointsOfTriangleForLine = line.GetPoints();

                for (std::size_t i = 0; i < 2; ++i) {
                    vertices.push_back(pointsOfTriangleForLine[i].Point_1.X);
                    vertices.push_back(pointsOfTriangleForLine[i].Point_1.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(pointsOfTriangleForLine[i].Point_2.X);
                    vertices.push_back(pointsOfTriangleForLine[i].Point_2.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(pointsOfTriangleForLine[i].Point_3.X);
                    vertices.push_back(pointsOfTriangleForLine[i].Point_3.Y);
                    vertices.push_back(0.0f);
                }

                const LDDrift::VecPos2D& p0 = points[previousPoint];
                const LDDrift::VecPos2D& p1 = points[currentPoint];
                const LDDrift::VecPos2D& p2 = points[nextPoint];

                LDDrift::VecPos2D normalLineOfLine1 = LDDrift::VecPos2D::NormalLine(p0, p1);
                LDDrift::VecPos2D normalLineOfLine2 = LDDrift::VecPos2D::NormalLine(p1, p2);

                LDDrift::VecPos2D firstPointOfTriangle = p1 + normalLineOfLine1 * halfThick;
                LDDrift::VecPos2D secondPointOfTriangle = p1 + normalLineOfLine2 * halfThick;

                vertices.push_back(firstPointOfTriangle.X);
                vertices.push_back(firstPointOfTriangle.Y);
                vertices.push_back(0.0f);
                vertices.push_back(secondPointOfTriangle.X);
                vertices.push_back(secondPointOfTriangle.Y);
                vertices.push_back(0.0f);
                vertices.push_back(p1.X);
                vertices.push_back(p1.Y);
                vertices.push_back(0.0f);
            }
        }

        void TrianglesForConcaveShape(std::vector<float>& vertices) const {
            std::vector<LDDrift::VecPos2D> points = shape->GetGlobalPoints();
            std::size_t pointCountOfShape = shape->GetPointCount();
            if (pointCountOfShape < 3) {
                throw std::runtime_error("this shape is not available");
            }
            for (std::size_t pointINdex = 0; pointINdex < pointCountOfShape; ++pointINdex) {
                if (points.size() == 3) {
                    vertices.push_back(points[0].X);
                    vertices.push_back(points[0].Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(points[1].X);
                    vertices.push_back(points[1].Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(points[2].X);
                    vertices.push_back(points[2].Y);
                    vertices.push_back(0.0f);
                    break;
                }
                const std::size_t point_A_number = pointINdex == 0 ? pointCountOfShape - 1 : pointINdex - 1;
                const std::size_t point_B_number = pointINdex;
                const std::size_t point_C_number = (pointINdex + 1) % pointCountOfShape;

                const LDDrift::VecPos2D& point_A = points[point_A_number];
                const LDDrift::VecPos2D& point_B = points[point_B_number];
                const LDDrift::VecPos2D& point_C = points[point_C_number];

                if (Cross(point_A, point_B, point_C) <= 0.0f) {
                    continue;
                }
                bool isEar = true;
                for (std::size_t point = 0; point < pointCountOfShape; ++point) {
                    if (point == point_A_number || point == point_B_number || point == point_C_number) {
                        continue;
                    }
                    if (LDDrift::PointHitTesting::pointHitTesting(points[point],
                                                                  std::vector<LDDrift::VecPos2D>{
                                                                      point_A, point_B, point_C
                                                                  })) {
                        isEar = false;
                        break;
                    }
                }
                if (isEar) {
                    vertices.push_back(point_A.X);
                    vertices.push_back(point_A.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(point_B.X);
                    vertices.push_back(point_B.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(point_C.X);
                    vertices.push_back(point_C.Y);
                    vertices.push_back(0.0f);
                    points.erase(points.begin() + static_cast<long int>(pointINdex));
                    --pointCountOfShape;
                    --pointINdex;
                }
            }
        }

        void TrianglesForConvexShape(std::vector<float>& vertices) const {
            // get center point position of shape
            LDDrift::VecPos2D CenterPos = {0, 0};
            const std::size_t shapePointNumber = shape->GetPointCount();
            for (std::size_t pointNumber = 0; pointNumber < shapePointNumber; ++pointNumber) {
                CenterPos += shape->GetGlobalPoint(pointNumber);
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
                vertices.push_back(shape->GetGlobalPoint(currentPoint).X);
                vertices.push_back(shape->GetGlobalPoint(currentPoint).Y);
                vertices.push_back(0.0f);
                vertices.push_back(shape->GetGlobalPoint(nextPoint).X);
                vertices.push_back(shape->GetGlobalPoint(nextPoint).Y);
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
            NPV_assert(shapePTR);
            shape = shapePTR;
        }

        [[nodiscard]] std::vector<float> CreateTriangles() const {
            const std::size_t pointNumber = shape->GetPointCount();
            if (pointNumber < 3) {
                std::cout <<
                    R"( The shape you are attempting to convert into a triangle is either already a triangle,
                        or its number of vertices is invalid.
                        Therefore, be mindful of the valid data you extract from this function.)" << std::endl;
                return std::vector<float>{0.0f};
            }
            if (pointNumber == 3) {
                std::vector<float> vertices;
                for (std::size_t pointIndex = 0; pointIndex < 3; ++pointIndex) {
                    const LDDrift::VecPos2D& point = shape->GetGlobalPoint(pointIndex);
                    vertices.push_back(point.X);
                    vertices.push_back(point.Y);
                    vertices.push_back(0.0f);
                }
                return vertices;
            }
            if (shape->IsHaveThickness() || !shape->IsFillShape()) {
                std::vector<float> vertices;
                this->TrianglesForThickShapes(vertices);
                return vertices;
            } else {
                if constexpr (std::is_same_v<ShapeType, LDDrift::ActorType::convex>) {
                    std::vector<float> vertices;
                    this->TrianglesForConvexShape(vertices);
                    return vertices;
                } else if constexpr (std::is_same_v<ShapeType, LDDrift::ActorType::concave>) {
                    std::vector<float> vertices;
                    try {
                        this->TrianglesForConcaveShape(vertices);
                    } catch (const std::runtime_error& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    return vertices;
                } else {
                    std::cout <<
                        R"( You did not submit a valid type for constructing a triangle on the shape.
                        You can choose between two categories of shapes: convex or concave.)";
                    return std::vector<float>{0.0f};
                }
            }
        }

        ~Triangulation() = default;
    };
}

#endif
