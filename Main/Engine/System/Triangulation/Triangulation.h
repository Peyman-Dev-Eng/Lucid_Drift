#ifndef LUCID_DRIFT_TRIANGLE_H
#define LUCID_DRIFT_TRIANGLE_H
#include <vector>
#include <Actors/Shapes/MainShape/Shape.h>

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
            for (std::size_t pointNumber = 0; pointNumber < shapePointNumber; ++pointNumber) {
                const LDDrift::VecPos2D& pointA = shape->GetPoint((pointNumber) % shapePointNumber);
                const LDDrift::VecPos2D& pointB = shape->GetPoint((pointNumber + 1) % shapePointNumber);
                const LDDrift::VecPos2D& pointC = shape->GetPoint((pointNumber + 2) % shapePointNumber);
                const float cross =
                    (pointB.X - pointA.X) * (pointC.Y - pointB.Y)
                    - (pointB.Y - pointA.Y) * (pointC.X - pointA.X);
                if (const bool isConvexCorner = cross * shape->ShapeIsConvex().pointDirection > 0.0f; !isConvexCorner) {
                    continue;
                }
            }
        }

        void TrianglesForConvexShape(std::vector<float>& vertices) const {
            // get center point position of shape
            LDDrift::VecPos2D CenterPos{0, 0};
            const std::size_t shapePointNumber = shape->GetPointCount();
            for (std::size_t pointNumber = 0; pointNumber < shapePointNumber; ++pointNumber) {
                CenterPos += shape->GetPoint(pointNumber);
            }
            CenterPos /= shapePointNumber;
            /////////////////////////////////////////////
            // create triangles
            for (std::size_t pointNumber = 0; pointNumber < shapePointNumber; ++pointNumber) {
                const std::size_t previousPointNumber = (pointNumber - 1) % pointNumber;
                const std::size_t currentPointNumber = pointNumber == (shapePointNumber - 1) ? 0 : pointNumber;
                vertices.push_back(CenterPos.X);
                vertices.push_back(CenterPos.Y);
                vertices.push_back(0.0f);
                vertices.push_back(shape->GetPoint(previousPointNumber).X);
                vertices.push_back(shape->GetPoint(previousPointNumber).Y);
                vertices.push_back(0.0f);
                vertices.push_back(shape->GetPoint(currentPointNumber).X);
                vertices.push_back(shape->GetPoint(currentPointNumber).Y);
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
                std::cerr << RED <<
                    R"( The shape you are attempting to convert into a triangle is either already a triangle,
                        or its number of vertices is invalid.
                        Therefore, be mindful of the valid data you extract from this function.)" << RESET << std::endl;
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

        ~Triangulation();
    };
}

#endif
