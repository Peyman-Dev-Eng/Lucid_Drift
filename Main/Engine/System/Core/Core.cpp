#include "Core.h"

namespace
{
    LDDrift::Scene* currentScene = nullptr;
}

LDDrift::Core::Core() = default;

void LDDrift::Core::InitCore() {
    oldC_outBuf = std::cout.rdbuf(consoleBuffer.rdbuf());
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
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL,
        LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_T
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
    camera.InitializeCameraSystem(this);
    render.SetCorePTR(this);
}

void LDDrift::Core::Begin() {
    this->InitCore();
}

void LDDrift::Core::EngineHandler() {
    using namespace std::chrono_literals;
    projectWatchTower.SetPaths();
    LDDrift::GuiLogic::SetProjectWatchTowerPtr(&projectWatchTower);
    while (window.ScreenIsOpen() && engineRun) {
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
        /*if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A)) {
            camera.MoveLeft();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D)) {
            camera.MoveRight();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W)) {
            camera.MoveUp();
        }
        if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S)) {
            camera.MoveDown();
        }*/
        LDDrift::input::Keyboard::Update();
        LDDrift::input::Mouse::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        if (gui.runGame) {
            LDDrift::EngineAPI::beginPlay();
            while (gui.runGame) {
                LDDrift::input::Keyboard::GetKeyInputEvent();
                LDDrift::input::Mouse::GetMouseInputEvent();
                LDDrift::GUI::BeginRenderGUI();
                window.ClearBuffer();
                LDDrift::EngineAPI::tick(LDDrift::func::GetDeltaTime());
                render.render();
                gui.SetTextForWindow(CONSOLE_WINDOW_NAME, consoleBuffer.str(), true);
                gui.UpdateWindow("Project Watch Tower");
                gui.EndRenderGUI();
                window.Update();
                LDDrift::input::Keyboard::Update();
                LDDrift::input::Mouse::Update();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
            LDDrift::EngineAPI::endPlay();
        }
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
