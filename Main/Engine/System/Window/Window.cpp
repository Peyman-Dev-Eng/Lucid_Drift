#include "Window.h"
#include <Renderer/Renderer.h>
#include <System/Core/Core.h>
#include "System/Input/input.h"
#include "SubSystems/Transform/Transform.h"

LDDrift::Window::Window() : renderer(nullptr) {
    GLB_assert(glfwInit())
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    settings.title = "NONE";
    settings.width = 500;
    settings.height = 500;
    settings.CanResize = false;
    settings.FillColorScreen = {0.0f, 0.0f, 0.0f, 1.0f};
    this->monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
}

void LDDrift::Window::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::Window::CreateWindow() {
    screen = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
    if (screen == nullptr) {
        const char* description = nullptr;
        const int code = glfwGetError(&description);

        std::cout << "GLFW window creation failed!\n";
        std::cout << "Error code: " << code << '\n';
        std::cout << "Description: "
            << (description ? description : "Unknown")
            << '\n';

        return;
    }
    settings.IsOpen = true;
    glfwMakeContextCurrent(screen);
    glEnable(GL_MULTISAMPLE);
    GLB_assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    glfwSetWindowUserPointer(screen, this);
}

LDDrift::VecPos2D LDDrift::Window::GetViewportSize() const {
    return {static_cast<float>(settings.viewPortWidth), static_cast<float>(settings.viewPortHeight)};
}

void LDDrift::Window::CreateFullscreenWindow() {
    glfwWindowHintString(
        GLFW_WAYLAND_APP_ID,
        "lucid-drift"
    );
    screen = glfwCreateWindow(mode->width, mode->height - 300, settings.title.c_str(), monitor, nullptr);
    if (screen == nullptr) {
        const char* description = nullptr;
        const int code = glfwGetError(&description);

        std::cout << "GLFW window creation failed!\n";
        std::cout << "Error code: " << code << '\n';
        std::cout << "Description: "
            << (description ? description : "Unknown")
            << '\n';

        return;
    }
    settings.IsOpen = true;
    glfwMakeContextCurrent(screen);
    GLB_assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    glfwSetWindowUserPointer(screen, this);
    glViewport(350, 180, mode->width - 350, mode->height - 180);
    settings.width = mode->width;
    settings.height = mode->height;
    settings.viewPortWidth = mode->width - 350;
    settings.viewPortHeight = mode->height - 180;
    glfwSetFramebufferSizeCallback(screen, LDDrift::Window::FrameBufferSizeCallback);
    LDDrift::Transform::widthScreen = settings.viewPortWidth;
    LDDrift::Transform::heightScreen = settings.viewPortHeight;
    LDDrift::Transform::halfWidthScreen = settings.viewPortWidth / 2;
    LDDrift::Transform::halfHeightScreen = settings.viewPortHeight / 2;

    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* pixels = stbi_load(
        "docs/images/LucidDrift_Blue_Water_Emblem.png",
        &width,
        &height,
        &channels,
        4
    );

    if (pixels == nullptr) {
        std::cerr << "Failed to load window icon!\n";
        std::cerr << "Working directory: "
            << std::filesystem::current_path() << '\n';
        std::cerr << "Reason: "
            << stbi_failure_reason() << '\n';
    }

    if (pixels) {
        GLFWimage icon{};
        icon.width = width;
        icon.height = height;
        icon.pixels = pixels;

        if (glfwGetPlatform() != GLFW_PLATFORM_WAYLAND) {
            glfwSetWindowIcon(screen, 1, &icon);
        }

        stbi_image_free(pixels);
    }

#ifdef __WIN32
    glfwSetScrollCallback(screen, LDDrift::input::Mouse::ScrollCallback);
#endif
}

void LDDrift::Window::SetTitle(const char* title) {
    std::string FinalTitle = title;
    FinalTitle += " ( Lucid-Drift ) ";
    glfwSetWindowTitle(screen, FinalTitle.c_str());
    settings.title = title;
}

void LDDrift::Window::SetSize(const int width, const int height) {
    glfwSetWindowSize(screen, width, height);
    settings.width = width;
    settings.height = height;
    core->gui.mainWindow.Resize();
    core->gui.consoleWindow.Resize();
    core->gui.projectWatchTowerWindow.Resize();
    settings.viewPortWidth = width - 350;
    settings.viewPortHeight = height - 180;
    glViewport(350, 180, settings.viewPortWidth, settings.viewPortHeight);
    LDDrift::Transform::widthScreen = settings.viewPortWidth;
    LDDrift::Transform::heightScreen = settings.viewPortHeight;
    LDDrift::Transform::halfWidthScreen = settings.viewPortWidth / 2;
    LDDrift::Transform::halfHeightScreen = settings.viewPortHeight / 2;
}

void LDDrift::Window::SetFillScreenColor(const LDDrift::VecCol& color) {
    settings.FillColorScreen = color;
}

void LDDrift::Window::SetRendererPTR(LDDrift::Renderer* rendererPTR) {
    renderer = rendererPTR;
}

void LDDrift::Window::ClearBuffer() const {
    glfwMakeContextCurrent(screen);
    glClearColor(settings.FillColorScreen.R, settings.FillColorScreen.G, settings.FillColorScreen.B,
                 settings.FillColorScreen.A);
    glClear(GL_COLOR_BUFFER_BIT);
    core->gui.mainWindow.Resize();
    core->gui.consoleWindow.Resize();
    core->gui.projectWatchTowerWindow.Resize();
    glViewport(350, 180, settings.viewPortWidth, settings.viewPortHeight);
}

void LDDrift::Window::SetPosition(const int x, const int y) {
    glfwSetWindowPos(screen, x, y);
    settings.pos_x = x;
    settings.pos_y = y;
}

void LDDrift::Window::DestroyWindow() const {
    glfwDestroyWindow(screen);
    glfwTerminate();
}

bool LDDrift::Window::ScreenIsOpen() const {
    return settings.IsOpen;
}

void LDDrift::Window::Update() {
    glfwMakeContextCurrent(screen);
    glfwSwapBuffers(screen);
    glfwPollEvents();
    if (glfwWindowShouldClose(screen)) {
        settings.IsOpen = false;
    }
}

void LDDrift::Window::FrameBufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    auto* currentWindow = static_cast<LDDrift::Window*>(glfwGetWindowUserPointer(window));
    currentWindow->settings.width = width;
    currentWindow->settings.height = height;
    currentWindow->renderer->SetWidthScreen(width - 350);
    currentWindow->renderer->SetHeightScreen(height - 180);
    currentWindow->renderer->RebuildShapes();
    currentWindow->core->gui.mainWindow.Resize();
    currentWindow->core->gui.consoleWindow.Resize();
    currentWindow->core->gui.projectWatchTowerWindow.Resize();
    currentWindow->settings.viewPortWidth = (width - 350);
    currentWindow->settings.viewPortHeight = (height - 180);
    LDDrift::Transform::widthScreen = currentWindow->settings.viewPortWidth;
    LDDrift::Transform::heightScreen = currentWindow->settings.viewPortHeight;
    LDDrift::Transform::halfWidthScreen = (currentWindow->settings.viewPortWidth / 2);
    LDDrift::Transform::halfHeightScreen = (currentWindow->settings.viewPortHeight / 2);
    glViewport(350, 180, width - 350, height - 180);
}

LDDrift::VecCol LDDrift::Window::GetFillScreenColor() const {
    return settings.FillColorScreen;
}

LDDrift::VecPos2D LDDrift::Window::GetWindowSize() const {
    return LDDrift::VecPos2D{static_cast<float>(settings.width), static_cast<float>(settings.height)};
}

LDDrift::VecPos2D LDDrift::Window::GetPosition() const {
    return LDDrift::VecPos2D{static_cast<float>(settings.pos_x), static_cast<float>(settings.pos_y)};
}

const char* LDDrift::Window::GetTitle() const {
    return settings.title.c_str();
}

LDDrift::VecPos2D LDDrift::Window::GetCenterPosition() const {
    return LDDrift::VecPos2D{static_cast<float>(settings.width) / 2, static_cast<float>(settings.height) / 2};
}

int LDDrift::Window::GetWidth() const {
    return settings.width;
}

int LDDrift::Window::GetHeight() const {
    return settings.height;
}

GLFWwindow* LDDrift::Window::GetWindow() const {
    return screen;
}

LDDrift::Window::~Window() {
    this->DestroyWindow();
}
