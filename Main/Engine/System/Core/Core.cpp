#include "Core.h"

namespace
{
    LDDrift::Scene* currentScene = nullptr;
}

LDDrift::Core::Core() = default;

void LDDrift::Core::InitCore() {
    camera.InitializeCameraSystem(this);
    oldC_outBuf = std::cout.rdbuf(consoleBuffer.rdbuf());
    projectWatchTower.CreateNewProject("TestProject");
    window.CreateFullscreenWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0, 0, 0, 1});
    render.SetCorePTR(this);
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
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LSHIFT,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_T,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S
    });
    gui.SetCorePTR(this);
    LDDrift::func::InitDeltaTime();
    LDDrift::EngineAPI::SetProjectWatchTowerPTR(&projectWatchTower);
    gui.SetCompilePTR(&compile);
    compile.init(&projectWatchTower);
    scene.SetRendererPTR(&render);
    scene.SetCorePTR(this);
    currentScene = &scene;
    codePathfinder.initializeCodePathfinder();
}

void LDDrift::Core::Begin() {
    this->InitCore();
}

void LDDrift::Core::CameraController() {
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A)) {
        camera.MoveLeft();
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D)) {
        camera.MoveRight();
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W)) {
        camera.MoveUp();
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S)) {
        camera.MoveDown();
    }

    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() == false &&
        LDDrift::input::Mouse::ScrollUp()) {
        if (camera.GetSpeed() >= 1)
            camera.AddSpeedCamera(1.0f);
        else {
            camera.AddSpeedCamera(0.1f);
        }
        render.UpdateViewMatrix();
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() == false &&
        LDDrift::input::Mouse::ScrollDown()) {
        if (camera.GetSpeed() >= 1)
            camera.SubSpeedCamera(1.0f);
        else {
            camera.SubSpeedCamera(0.1f);
        }
        render.UpdateViewMatrix();
    }

    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() &&
        LDDrift::input::Mouse::ScrollDown()) {
        camera.SubZoomCamera(0.1f);
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() &&
        LDDrift::input::Mouse::ScrollUp()) {
        camera.AddZoomCamera(0.1f);
    }
}

void LDDrift::Core::RunEngineFrame() {
    LDDrift::input::Keyboard::GetKeyInputEvent();
    LDDrift::input::Mouse::GetMouseInputEvent();
    LDDrift::GUI::BeginRenderGUI();
    window.ClearBuffer();
    render.render();
    gui.SetTextForWindow(CONSOLE_WINDOW_NAME, consoleBuffer.str(), true);
    gui.UpdateWindow("Project Watch Tower");
    for (const auto& path : projectWatchTower.GetPaths()) {
        gui.SetTextForWindow("Project Watch Tower", path.string(), false);
    }
    gui.EndRenderGUI();
    window.Update();
    CameraController();
    LDDrift::input::Keyboard::Update();
    LDDrift::input::Mouse::Update();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

void LDDrift::Core::RunGameFrame() {
    if (gui.runGame == false) {
        return;
    }
    EngineAPI::beginPlay();
    while (gui.runGame) {
        input::Keyboard::GetKeyInputEvent();
        input::Mouse::GetMouseInputEvent();
        GUI::BeginRenderGUI();
        window.ClearBuffer();
        EngineAPI::tick(LDDrift::func::GetDeltaTime());
        render.render();
        gui.SetTextForWindow(CONSOLE_WINDOW_NAME, consoleBuffer.str(), true);
        gui.UpdateWindow("Project Watch Tower");
        gui.EndRenderGUI();
        window.Update();
        input::Keyboard::Update();
        input::Mouse::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    EngineAPI::endPlay();
}

void LDDrift::Core::EngineHandler() {
    using namespace std::chrono_literals;
    projectWatchTower.SetPaths();
    LDDrift::GuiLogic::SetProjectWatchTowerPtr(&projectWatchTower);
    while (window.ScreenIsOpen() && engineRun) {
        RunEngineFrame();
        RunGameFrame();
    }
}

LDDrift::Core::~Core() {
    std::cout.rdbuf(oldC_outBuf);
    LDDrift::input::Keyboard::Destroy();
    LDDrift::input::Mouse::Destroy();
    LDDrift::EngineAPI::DestroyEngineAPI();
    window.DestroyWindow();
    if (currentScene == &scene) {
        currentScene = nullptr;
    }
}

LDDrift::Scene* LDDrift::func::GetSceneObjectPointer() {
    return currentScene;
}
