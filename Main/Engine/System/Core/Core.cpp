#include "Core.h"

#include "API/EngineAPI.h"

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
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SPACE
    });
    gui.SetCorePTR(this);
    oldC_outBuf = std::cout.rdbuf(consoleBuffer.rdbuf());
    LDDrift::func::InitDeltaTime();
    LDDrift::EngineAPI::SetProjectWatchTowerPTR(&projectWatchTower);
}

void LDDrift::Core::Begin() {
    this->InitCore();
}

void LDDrift::Core::EngineHandler() {
    projectWatchTower.SetPaths();
    LDDrift::GuiLogic::SetProjectWatchTowerPtr(&projectWatchTower);
    while (window.ScreenIsOpen()) {
        currentTime = glfwGetTime();
        deltaTime = static_cast<float>(currentTime - lastTime);
        LDDrift::input::Keyboard::GetKeyInputEvent();
        LDDrift::input::Mouse::GetMouseInputEvent();
        LDDrift::GUI::BeginRenderGUI();
        window.ClearBuffer();
        if (LDDrift::input::Keyboard::IsKeyPressed(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC)) {
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
}

LDDrift::Core::~Core() {
    std::cout.rdbuf(oldC_outBuf);
    LDDrift::input::Keyboard::Destroy();
    LDDrift::input::Mouse::Destroy();
    window.DestroyWindow();
}
