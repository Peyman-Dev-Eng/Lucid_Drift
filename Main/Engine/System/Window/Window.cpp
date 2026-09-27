#include "Window.h"

LDDrift::Window::Window() : renderer(nullptr) {
    GLB_assert(glfwInit())
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

        std::cerr << "GLFW window creation failed!\n";
        std::cerr << "Error code: " << code << '\n';
        std::cerr << "Description: "
            << (description ? description : "Unknown")
            << '\n';

        return;
    }
    settings.IsOpen = true;
    glfwMakeContextCurrent(screen);
    GLB_assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    glfwSetWindowUserPointer(screen, this);
}

void LDDrift::Window::CreateFullscreenWindow() {
    screen = glfwCreateWindow(mode->width, mode->height, settings.title.c_str(), monitor, nullptr);
    if (screen == nullptr) {
        const char* description = nullptr;
        const int code = glfwGetError(&description);

        std::cerr << "GLFW window creation failed!\n";
        std::cerr << "Error code: " << code << '\n';
        std::cerr << "Description: "
            << (description ? description : "Unknown")
            << '\n';

        return;
    }
    settings.IsOpen = true;
    glfwMakeContextCurrent(screen);
    GLB_assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    glfwSetWindowUserPointer(screen, this);
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
    glViewport(0,0, width, height);
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
    currentWindow->renderer->SetWidthScreen(width);
    currentWindow->renderer->SetHeightScreen(height);
    currentWindow->renderer->RebuildShapes();
    glViewport(0,0, width, height);
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
