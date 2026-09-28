#include <iostream>
#include <thread>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Assertions.h"
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "SubSystems/PointHitTesting/PointHitTesting.h"
#include <System/Triangulation/Triangulation.h>
#include <System/Window/Window.h>
#include <Renderer/Renderer.h>
#include <System/Input/input.h>
#include <System/GUI/GUI.h>
#include "../FileSystemHandling/FileSystemHND.h"
static std::string text =
    "Hello Peyman\n"
    "How Are You Today?\n"
    "Can You Help Me?\n"
    "I am a programmer\n";

int main() {
    LDDrift::Window window;
    window.CreateFullscreenWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0, 0, 0, 1});
    window.SetSize(1920, 1080);
    LDDrift::Actors::Circle circle;
    circle.SetScreenSize(window.GetWindowSize());
    circle.SetRadius(100);
    circle.SetPointCount(45);
    circle.SetSpeed(10);
    circle.SetPosition({600, 450});
    circle.Rebuild();
    circle.SetFillColor(true);
    circle.SetAllPointsColor({1, 0, 0, 1});
    circle.SetOriginalPositionToCenter();
    LDDrift::Renderer renderer(window.GetWidth(), window.GetHeight());
    renderer.AddShapeToRender(&circle);
    renderer.SendDataToGPU();
    window.SetRendererPTR(&renderer);
    LDDrift::input::Keyboard::Init();
    LDDrift::GUI gui(window.GetWindow());
    gui.CreateNewWindow("TEST", false, text, {10, 50});
    gui.CreateNewEditor("Code Editor", true);
    glfwSetFramebufferSizeCallback(window.GetWindow(), LDDrift::Window::FrameBufferSizeCallback);
    while (window.ScreenIsOpen()) {
        LDDrift::input::Keyboard::GetKeyInputEvent();
        window.ClearBuffer();
        LDDrift::GUI::BeginRenderGUI();
        gui.EndRenderGUI();
        renderer.render();
        window.Update();
        LDDrift::input::Keyboard::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LDDrift::input::Keyboard::Destroy();
    window.DestroyWindow();
    return 0;
}
