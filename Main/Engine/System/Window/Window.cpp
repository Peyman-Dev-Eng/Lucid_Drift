#include "Window.h"
#include <Renderer/Renderer.h>

#include "System/Input/input.h"

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

LDDrift::VecPos2D LDDrift::Window::GetViewportSize() {
    return {VIEWPORT_WINDOW_WIDTH, VIEWPORT_WINDOW_HEIGHT};
}

void LDDrift::Window::CreateFullscreenWindow() {
    screen = glfwCreateWindow(mode->width, mode->height, settings.title.c_str(), monitor, nullptr);
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
    glViewport(350, 180, VIEWPORT_WINDOW_WIDTH, VIEWPORT_WINDOW_WIDTH);
    settings.width = mode->width;
    settings.height = mode->height;
    glfwSetFramebufferSizeCallback(screen, LDDrift::Window::FrameBufferSizeCallback);

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
    glViewport(PROJECT_WATCH_TOWER_X_SIZE, CONSOLE_Y_SIZE,
               width - PROJECT_WATCH_TOWER_X_SIZE, height - CONSOLE_Y_SIZE);
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
    const int viewportWidth = std::max(0, settings.width - PROJECT_WATCH_TOWER_X_SIZE);

    const int viewportHeight = std::max(0, settings.height - CONSOLE_Y_SIZE);
    glViewport(PROJECT_WATCH_TOWER_X_SIZE, CONSOLE_Y_SIZE, viewportWidth, viewportHeight);
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
    currentWindow->renderer->SetWidthScreen(width - PROJECT_WATCH_TOWER_X_SIZE);
    currentWindow->renderer->SetHeightScreen(height - CONSOLE_Y_SIZE);
    currentWindow->renderer->RebuildShapes();
    glViewport(350, 180, width, height - CONSOLE_Y_SIZE);
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
