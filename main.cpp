#include <iostream>
#include <thread>

#include "Assertions.h"
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "SubSystems/PointHitTesting/PointHitTesting.h"
#include <System/Triangulation/Triangulation.h>
#include <System/Window/Window.h>
#include <Renderer/Renderer.h>
#include <System/Input/input.h>

int main() {
    LDDrift::Window window;
    window.CreateWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0,0,0,1});
    window.SetSize(1200,900);
    LDDrift::Actors::Circle circle;
    std::cout << window.GetWidth() << ",, " << window.GetHeight() << std::endl;
    circle.SetScreenSize(window.GetWindowSize());
    circle.SetRadius(100);
    circle.SetPointCount(45);
    circle.SetSpeed(0.01);
    circle.SetPosition({600, 450});
    circle.Rebuild();
    circle.SetFillColor(true);
    circle.SetAllPointsColor({1,0,0,1});
    circle.SetOriginalPositionToCenter();
    LDDrift::Renderer renderer(window.GetWidth(), window.GetHeight());
    renderer.AddShapeToRender(&circle);
    renderer.SendDataToGPU();
    LDDrift::input::Keyboard::Init();
    while (window.ScreenIsOpen()) {
        LDDrift::input::Keyboard::GetKeyInputEvent();
        window.ClearBuffer();
        if (LDDrift::input::Keyboard::IsKeyHeld(static_cast<LD_lint>(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A))) {
            circle.Move(LDDrift::Actors::Dir::LEFT);
            renderer.UpdateShapeData();
            renderer.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(static_cast<LD_lint>(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W))) {
            circle.Move(LDDrift::Actors::Dir::UP);
            renderer.UpdateShapeData();
            renderer.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(static_cast<LD_lint>(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D))) {
            circle.Move(LDDrift::Actors::Dir::RIGHT);
            renderer.UpdateShapeData();
            renderer.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(static_cast<LD_lint>(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S))) {
            circle.Move(LDDrift::Actors::Dir::DOWN);
            renderer.UpdateShapeData();
            renderer.SendDataToGPU();
        }
        renderer.render();
        window.Update();
        LDDrift::input::Keyboard::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LDDrift::input::Keyboard::Destroy();
    window.DestroyWindow();
    return 0;
}
