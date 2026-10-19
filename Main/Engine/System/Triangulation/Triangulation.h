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
            std::size_t pointCountOfShape = shape->GetPointCount();
            if (pointCountOfShape < 3) {
                throw std::runtime_error("this shape is not available");
            }
            for (std::size_t pointIndex = 0; pointIndex < pointCountOfShape; ++pointIndex) {

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
                vertices.push_back(LDDrift::Transform::TransformToNDC_Position(CenterPos.X, 'x'));
                vertices.push_back(LDDrift::Transform::TransformToNDC_Position(CenterPos.Y, 'y'));
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
            NPV_assert(shapePTR);
            shape = shapePTR;
        }

        [[nodiscard]] std::vector<float> CreateTriangles() const {
            const std::size_t pointNumber = shape->GetPointCount();
            if (pointNumber < 3) {
                std::cerr <<
                    R"( The shape you are attempting to convert into a triangle is either already a triangle,
                        or its number of vertices is invalid.
                        Therefore, be mindful of the valid data you extract from this function.)" << std::endl;
                return std::vector<float>{0.0f};
            }
            if (pointNumber == 3) {
                std::vector<float> vertices;
                for (std::size_t pointIndex = 0; pointIndex < 3; ++pointIndex) {
                    const LDDrift::VecPos2D& point = shape->GetNDC_Point(pointIndex);
                    vertices.push_back(point.X);
                    vertices.push_back(point.Y);
                    vertices.push_back(0.0f);
                }
                return vertices;
            }
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
