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
#include <ProjectWatchTower.h>
#include <System/Input/input.h>
#include <System/GUI/GUI.h>
#include <System/Core/Core.h>
static std::string text =
    "Hello Peyman\n"
    "How Are You Today?\n"
    "Can You Help Me?\n"
    "I am a programmer\n";


int main() {
    LDDrift::Core core;
    core.Begin();
    while (core.window.ScreenIsOpen()) {
        LDDrift::input::Keyboard::GetKeyInputEvent();
        LDDrift::input::Mouse::GetMouseInputEvent();
        core.window.ClearBuffer();
        LDDrift::GUI::BeginRenderGUI();
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC)) {
            break;
        }
        core.gui.EndRenderGUI();
        core.render.render();
        core.window.Update();
        LDDrift::input::Keyboard::Update();
        LDDrift::input::Mouse::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LDDrift::input::Keyboard::Destroy();
    LDDrift::input::Mouse::Destroy();
    core.window.DestroyWindow();
    return 0;
}
