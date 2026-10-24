#ifndef LUCID_DRIFT_TRIANGLE_H
#define LUCID_DRIFT_TRIANGLE_H
#define UPPER_BOUND 100
#define MITER 0
#define ROUND 1
#define BEVEL 2
#include <vector>
#include <algorithm>
#include <numbers>
#include <cmath>
#include <typeinfo>
#include <Actors/Shapes/MainShape/Shape.h>
#include <SubSystems/PointHitTesting/PointHitTesting.h>

namespace LDDrift
{
    template <typename ShapeType>
    class Triangulation final
    {
    private: // join line algorithm functions

        /// bevel join lining

        [[nodiscard]] std::vector<float> BevelAlgorithm() const {
            std::vector<float> vertices;
            const std::size_t pointCount = shape->GetPointCount();
            const std::vector<LDDrift::VecPos2D>& points = shape->GetGlobalPoints();
            const float halfThick = shape->GetThickness() / 2.0f;

            for (std::size_t point = 0; point < pointCount; ++point) {
                const std::size_t previousPointNumber = (point + pointCount - 1) % pointCount;
                const std::size_t currentPointNumber = point;
                const std::size_t nextPointNumber = (point + 1) % pointCount;

                const LDDrift::VecPos2D& previousPoint = points[previousPointNumber];
                const LDDrift::VecPos2D& currentPoint = points[currentPointNumber];
                const LDDrift::VecPos2D& nextPoint = points[nextPointNumber];


                LDDrift::Actors::Line line(points[currentPointNumber], points[nextPointNumber]);
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

                const LDDrift::VecPos2D distanceOfLine1 = currentPoint - previousPoint;
                const LDDrift::VecPos2D distanceOfLine2 = nextPoint - currentPoint;

                const float length1 = std::sqrt(
                    distanceOfLine1.X * distanceOfLine1.X + distanceOfLine1.Y * distanceOfLine1.Y);
                const float length2 = std::sqrt(
                    distanceOfLine2.X * distanceOfLine2.X + distanceOfLine2.Y * distanceOfLine2.Y);

                const LDDrift::VecPos2D N1 = LDDrift::VecPos2D{-distanceOfLine1.Y, distanceOfLine1.X} / length1;
                const LDDrift::VecPos2D N2 = LDDrift::VecPos2D{-distanceOfLine2.Y, distanceOfLine2.X} / length2;

                const float cross = Cross(distanceOfLine1, distanceOfLine2);

                if (std::abs(cross) <= 1e-6f * length1 * length2)
                    continue;

                const float side = cross > 0.0 ? -1.0f : 1.0f;

                const LDDrift::VecPos2D resultPoint1 = currentPoint + (N1 * (halfThick * side));
                const LDDrift::VecPos2D resultPoint2 = currentPoint + (N2 * (halfThick * side));

                vertices.push_back(resultPoint1.X);
                vertices.push_back(resultPoint1.Y);
                vertices.push_back(0.0f);
                vertices.push_back(resultPoint2.X);
                vertices.push_back(resultPoint2.Y);
                vertices.push_back(0.0f);
                vertices.push_back(currentPoint.X);
                vertices.push_back(currentPoint.Y);
                vertices.push_back(0.0f);
            }
            return vertices;
        }

        /// round line joining

        /*[[nodiscard]] std::vector<float> RoundAlgorithm() const {
            std::vector<float> vertices;
            const std::size_t pointCountOfShape = shape->GetPointCount();
            const std::vector<LDDrift::VecPos2D>& points = shape->GetGlobalPoints();
            const float thick = shape->GetThickness();
            const float halfThick = thick / 2;
            for (std::size_t point = 0; point < pointCountOfShape; ++point) {
                const std::size_t previousPointNumber = (point + pointCountOfShape - 1) % pointCountOfShape;
                const std::size_t currentPointNumber = point;
                const std::size_t nextPointNumber = (point + 1) % pointCountOfShape;

                const LDDrift::VecPos2D& previousPoint = points[previousPointNumber];
                const LDDrift::VecPos2D& currentPoint = points[currentPointNumber];
                const LDDrift::VecPos2D& nextPoint = points[nextPointNumber];

                LDDrift::Actors::Line line(currentPoint, nextPoint);
                line.SetThickness(thick);
                line.SetScreenSize(shape->GetScreenSize());
                line.CreateTriangles();

                const std::vector<LDDrift::Actors::Line::PNT>& pointOfTriangles = line.GetPoints();

                for (std::size_t pointTriangleIndex = 0; pointTriangleIndex < 2; ++pointTriangleIndex) {
                    vertices.push_back(pointOfTriangles[pointTriangleIndex].Point_1.X);
                    vertices.push_back(pointOfTriangles[pointTriangleIndex].Point_1.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(pointOfTriangles[pointTriangleIndex].Point_2.X);
                    vertices.push_back(pointOfTriangles[pointTriangleIndex].Point_2.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(pointOfTriangles[pointTriangleIndex].Point_3.X);
                    vertices.push_back(pointOfTriangles[pointTriangleIndex].Point_3.Y);
                    vertices.push_back(0.0f);
                }

                const LDDrift::VecPos2D normalLine1 = LDDrift::VecPos2D::NormalLine(previousPoint, currentPoint);
                const LDDrift::VecPos2D normalLine2 = LDDrift::VecPos2D::NormalLine(currentPoint, nextPoint);

                const LDDrift::VecPos2D p1 = currentPoint + normalLine1 * halfThick;
                const LDDrift::VecPos2D p2 = currentPoint + normalLine2 * halfThick;

                const LDDrift::VecPos2D A = p1 - currentPoint;
                const LDDrift::VecPos2D B = p2 - currentPoint;

                const float a = std::atan2(A.Y, A.X);
                const float b = std::atan2((B.Y), B.X);

                const float angleDifference = std::remainder(b - a, 2.0f * std::numbers::pi_v<float>);

                const int segments = static_cast<int>(std::ceil(
                    std::abs(angleDifference) * 180.0f / std::numbers::pi_v<float>));

                float previous_X = p1.X;
                float previous_Y = p1.Y;

                for (int i = 0; i <= segments; ++i) {
                    const float t = static_cast<float>(i) / static_cast<float>(segments);
                    const float angle = a + angleDifference * t;

                    const float x = currentPoint.X + halfThick * std::cos(angle);
                    const float y = currentPoint.Y + halfThick * std::sin(angle);

                    vertices.push_back(currentPoint.X);
                    vertices.push_back(currentPoint.Y);
                    vertices.push_back(0.0f);
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(0.0f);
                    vertices.push_back(previous_X);
                    vertices.push_back(previous_Y);
                    vertices.push_back(0.0f);

                    previous_X = x;
                    previous_Y = y;
                }
            }
            return vertices;
        }*/

    private:
        LDDrift::Actors::Shape* shape;

    public: // functions

        static float Cross(const LDDrift::VecPos2D& vec1, const LDDrift::VecPos2D& vec2) {
            return vec1.X * vec2.Y - vec1.Y * vec2.X;
        }

        static float Cross(const VecPos2D& a, const VecPos2D& b, const VecPos2D& c) {
            return (b.X - a.X) * (c.Y - a.Y) -
                (b.Y - a.Y) * (c.X - a.X);
        }

        static float SignedArea2(const std::vector<LDDrift::VecPos2D>& vertices) {
            float area = 0.0f;

            for (std::size_t i = 0; i < vertices.size(); ++i) {
                const auto& a = vertices[i];
                const auto& b = vertices[(i + 1) % vertices.size()];

                area += a.X * b.Y - b.X * a.Y;
            }

            return area;
        }

    private:
        void TrianglesForThickShapes(std::vector<float>& vertices) const {
            const std::optional<LDDrift::JoinLineType> joinLineAlg = shape->GetJoinLineAlgorithm();
            if (!joinLineAlg.has_value()) {
                std::cout << "Undefined Line Connection Algorithm" << std::endl;
                return;
            }
            if (joinLineAlg.value() == LDDrift::JoinLineType::Bevel) {
                vertices = BevelAlgorithm();
                return;
            }
            /*if (joinLineAlg.value() == LDDrift::JoinLineType::Round) {
                vertices = RoundAlgorithm();
                return;
            }*/
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
            if (pointNumber == 3 && !shape->IsHaveThickness()) {
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
