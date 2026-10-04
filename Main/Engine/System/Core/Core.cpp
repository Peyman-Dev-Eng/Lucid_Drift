#include "Core.h"

#include "GuiLogic.h"

LDDrift::Core::Core() = default;

void LDDrift::Core::InitCore() {
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
}

void LDDrift::Core::Begin() {
    this->InitCore();
    gui.CreateNewWindow("Project Watch Tower", false, true,
                        "", {0, 720}, {350, 360});
    gui.CreateNewWindow("Project Manager", false, true,
                        "", {0, 600}, {350, 120});
    gui.CreateNewWindow("Console", false, true,
                        "", {350, 900}, {1570, 180});
    gui.CreateNewWindow("Main Window", false, true,
                        "", {0, 0}, {350, 600});
    polygon = new LDDrift::Actors::Polygon;
    polygon->SetFillColor(true);
    polygon->SetPointCount(4);
    polygon->SetScreenSize(window.GetWindowSize());
    polygon->SetPoint(0, {0.5, 0.5});
    polygon->SetPoint(1, {-0.5, 0.5});
    polygon->SetPoint(2, {0.5, -0.5});
    polygon->SetPoint(3, {-0.5, -0.5});
    polygon->SetSpeed(5);
    polygon->SetAllPointsColor({1, 0, 0, 1});
    render.AddShapeToRender(polygon);
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
            polygon->Move(LDDrift::Actors::Dir::LEFT);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D)) {
            polygon->Move(LDDrift::Actors::Dir::RIGHT);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W)) {
            polygon->Move(LDDrift::Actors::Dir::UP);
            render.UpdateShapeData();
            render.SendDataToGPU();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S)) {
            polygon->Move(LDDrift::Actors::Dir::DOWN);
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
    delete polygon;
}
