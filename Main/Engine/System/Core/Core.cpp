#include "Core.h"

#include "GuiLogic.h"

LDDrift::Core::Core() = default;

void LDDrift::Core::Begin() {
    projectWatchTower.CreateNewProject("TestProject");
    window.CreateFullscreenWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0, 0, 0, 1});
    render.Initialize();
    render.SetWidthScreen(window.GetWidth());
    render.SetHeightScreen(window.GetHeight());
    window.SetRendererPTR(&render);
    gui.Initialize(window.GetWindow());
    gui.SetProjectWatchTower_PTR(&projectWatchTower);
    LDDrift::input::Keyboard::Init();
    LDDrift::input::Mouse::Init();
    LDDrift::input::Keyboard::SetKeyTarget({
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D
    });
    gui.SetCorePTR(this);
    oldC_outBuf = std::cout.rdbuf(consoleBuffer.rdbuf());
    gui.CreateNewWindow("Project Watch Tower", false, true,
                        "", {0, 720}, {350, 360});
    gui.CreateNewWindow("Project Manager", false, true,
                        "", {0, 600}, {350, 120});
    gui.CreateNewWindow("Console", false, true,
                        "", {350, 900}, {1570, 180});
    gui.CreateNewWindow("Main Window", false, true,
                        "", {0, 0}, {350, 600});
    circle = new LDDrift::Actors::Circle(100.0f);
    circle->Rebuild(window.GetWidth(), window.GetHeight());
    circle->SetAllPointsColor({1, 0, 1, 1});
    circle->SetSpeed(5);
    circle->SetFillColor(true);
    render.AddShapeToRender(circle);
    render.SendDataToGPU();
}

void LDDrift::Core::EngineHandler() {
    projectWatchTower.SetPaths();
    LDDrift::GuiLogic::SetProjectWatchTowerPtr(&projectWatchTower);
    while (window.ScreenIsOpen()) {
        LDDrift::input::Keyboard::GetKeyInputEvent();
        LDDrift::input::Mouse::GetMouseInputEvent();
        LDDrift::GUI::BeginRenderGUI();
        window.ClearBuffer();
        if (LDDrift::input::Keyboard::IsKeyPressed(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC)) {
            return;
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A)) {
            circle->Move(LDDrift::Actors::Dir::LEFT);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D)) {
            circle->Move(LDDrift::Actors::Dir::RIGHT);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W)) {
            circle->Move(LDDrift::Actors::Dir::UP);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S)) {
            circle->Move(LDDrift::Actors::Dir::DOWN);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        render.render();
        gui.SetTextForWindow(CONSOLE_WINDOW_NAME, consoleBuffer.str(), true);
        gui.UpdateWindow("Project Watch Tower");
        for (const auto& path : projectWatchTower.GetPaths()) {
            gui.SetTextForWindow("Project Watch Tower", path.string(), false);
        }

        gui.EndRenderGUI();
        window.Update();
        LDDrift::input::Keyboard::Update();
        LDDrift::input::Mouse::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

LDDrift::Core::~Core() {
    std::cout.rdbuf(oldC_outBuf);
    LDDrift::input::Keyboard::Destroy();
    LDDrift::input::Mouse::Destroy();
    window.DestroyWindow();
    delete circle;
}
