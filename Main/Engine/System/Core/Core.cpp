#include "Core.h"

LDDrift::Core::Core() = default;

void LDDrift::Core::InitCore() {
    oldC_outBuf = std::cout.rdbuf(consoleBuffer.rdbuf());
    projectWatchTower.CreateNewProject("TestProject");
    window.SetCorePTR(this);
    window.CreateFullscreenWindow();
    window.SetTitle("TEST");
    window.SetFillScreenColor({0, 0, 0, 1});
    camera.InitializeCameraSystem(this);
    shape_render.SetCorePTR(this);
    shape_render.Initialize();
    shape_render.SetWidthScreen(window.GetWidth());
    shape_render.SetHeightScreen(window.GetHeight());
    window.SetRendererPTR(&shape_render);
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
    sceneManager.SetCorePTR(this);
    sceneManager.GetCurrentScene()->SetRendererPTR(&shape_render);
    sceneManager.GetCurrentScene()->SetCorePTR(this);
    sceneManager.Initialize();
    codePathfinder.initializeCodePathfinder();
    Write_Read_UserProjectSetting.SetCore_PTR(this);
    Write_Read_UserProjectSetting.SetProjectWatchTowerPTR(&this->projectWatchTower);
    Write_Read_UserProjectSetting.CreateSettingFolder();
    Write_Read_UserProjectSetting.ReadSettingsOfUserProject();
    textureRender.SetCorePTR(this);
    textureRender.Initialize();
    mainRenderer.SetCorePTR(this);
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
        camera.AddSpeedCamera(5.0f);
        const auto viewProjection = mainRenderer.UpdateViewMatrix();
        shape_render.SetViewMatrix(viewProjection);
        textureRender.SetViewMatrix(viewProjection);
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() == false &&
        LDDrift::input::Mouse::ScrollDown()) {
        camera.SubSpeedCamera(5.0f);
        const auto viewProjection = mainRenderer.UpdateViewMatrix();
        shape_render.SetViewMatrix(viewProjection);
        textureRender.SetViewMatrix(viewProjection);
    }

    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() &&
        LDDrift::input::Mouse::ScrollDown()) {
        camera.SubZoomCamera(0.1f);
        const auto viewProjection = mainRenderer.UpdateViewMatrix();
        shape_render.SetViewMatrix(viewProjection);
        textureRender.SetViewMatrix(viewProjection);
    }
    if (LDDrift::input::Keyboard::IsKeyHeld(LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL) &&
        LDDrift::input::Mouse::IsRightMouseButtonHeld() &&
        LDDrift::input::Mouse::ScrollUp()) {
        camera.AddZoomCamera(0.1f);
        const auto viewProjection = mainRenderer.UpdateViewMatrix();
        shape_render.SetViewMatrix(viewProjection);
        textureRender.SetViewMatrix(viewProjection);
    }
}

void LDDrift::Core::RunEngineFrame() {
    LDDrift::func::TickDeltaTime();
    LDDrift::input::Keyboard::GetKeyInputEvent();
    LDDrift::input::Mouse::GetMouseInputEvent();
    LDDrift::GUI::BeginRenderGUI();
    LDDrift::Core::CameraController();
    window.ClearBuffer();
    shape_render.render();
    textureRender.Render();
    gui.consoleWindow.SetText(consoleBuffer.str());
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

void LDDrift::Core::RunGameFrame() {
    if (gui.runGame == false) {
        return;
    }
    EngineAPI::beginPlay();
    while (gui.runGame) {
        LDDrift::func::TickDeltaTime();
        input::Keyboard::GetKeyInputEvent();
        input::Mouse::GetMouseInputEvent();
        GUI::BeginRenderGUI();
        window.ClearBuffer();
        EngineAPI::tick(LDDrift::func::GetDeltaTime());
        shape_render.render();
        gui.consoleWindow.SetText(consoleBuffer.str());
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
    projectWatchTower.SetPaths();
    while (window.ScreenIsOpen() && engineRun) {
        RunEngineFrame();
        RunGameFrame();
    }
    userProjectSetting.SetSettings(this);
}

void LDDrift::Core::End() {
    Write_Read_UserProjectSetting.WriteSettingsOfUserProject();
    std::cout.rdbuf(oldC_outBuf);
    LDDrift::input::Keyboard::Destroy();
    LDDrift::input::Mouse::Destroy();
    LDDrift::EngineAPI::DestroyEngineAPI();
    window.DestroyWindow();
}

LDDrift::Core::~Core() = default;
