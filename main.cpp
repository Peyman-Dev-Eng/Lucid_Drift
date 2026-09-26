#include <iostream>
#include "Assertions.h"
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "SubSystems/PointHitTesting/PointHitTesting.h"
#include <System/Triangulation/Triangulation.h>

int main() {
    LDDrift::Actors::Circle circle;
    circle.SetRadius(40);
    circle.SetSpeed(10);
    circle.SetScreenSize(LDDrift::VecPos2D{1920, 1080});
    circle.SetPosition({960,540});
    circle.SetPointCount(45);
    circle.SetAllPointsColor({1.0,0.0,0.0,0.0});
    circle.SetOriginalPositionToCenter();
    const LDDrift::Triangulation<LDDrift::ActorType::concave> triangulation(&circle);
    const std::vector<float> vertices = triangulation.CreateTriangles();
    std::cout << vertices.size() << std::endl;
    return 0;
}
