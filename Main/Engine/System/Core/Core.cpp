#include "Core.h"

#include "GuiLogic.h"

LDDrift::Core::Core() = default;

void LDDrift::Core::Begin() {
    projectWatchTower.CreateNewProject("TestProject");
    window.CreateFullscreenWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0, 0, 0, 1});
    render.Initialize();
    window.SetRendererPTR(&render);
    gui.Initialize(window.GetWindow());
    gui.SetProjectWatchTower_PTR(&projectWatchTower);
    LDDrift::input::Keyboard::Init();
    LDDrift::input::Mouse::Init();
    LDDrift::input::Keyboard::SetKeyTarget({
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC
    });
    gui.SetCorePTR(this);
    oldCoutBuf = std::cout.rdbuf(consoleBuffer.rdbuf());
    gui.CreateNewWindow("Project Watch Tower", false, true,
                        "", {0, 0}, {350, 540});
    gui.CreateNewWindow("Project Manager", false, true,
                        "", {0, 540}, {350, 540});
    gui.CreateNewWindow("Console", false, true,
                        "", {350, 900}, {1570, 180});
}

void LDDrift::Core::EngineHandler() {
    projectWatchTower.SetPaths();
    LDDrift::GuiLogic::SetProjectWatchTowerPtr(&projectWatchTower);
    while (window.ScreenIsOpen()) {
        LDDrift::input::Keyboard::GetKeyInputEvent();
        LDDrift::input::Mouse::GetMouseInputEvent();
        LDDrift::GUI::BeginRenderGUI();
        window.ClearBuffer();
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC)) {
            return;
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
    std::cout.rdbuf(oldCoutBuf);
}

LDDrift::Core::~Core() = default;
