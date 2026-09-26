#include <iostream>
#include "Assertions.h"
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "SubSystems/PointHitTesting/PointHitTesting.h"
#include <System/Triangulation/Triangulation.h>
#include <System/Window/Window.h>
#include <Renderer/Renderer.h>

int main() {
    LDDrift::Window window;
    window.CreateWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0,0,0,1});
    window.SetSize(1200,900);
    LDDrift::Actors::Circle circle;
    circle.SetScreenSize(window.GetWindowSize());
    circle.SetRadius(40);
    circle.SetPointCount(45);
    circle.SetFillColor(true);
    circle.SetAllPointsColor({1,0,0,1});
    circle.SetOriginalPositionToCenter();
    LDDrift::Renderer renderer(window.GetWidth(), window.GetHeight());
    renderer.AddShapeToRender(&circle);
    while (window.ScreenIsOpen()) {
        window.ClearBuffer();
        renderer.render();
        window.Update();
    }
    window.DestroyWindow();
    return 0;
}
