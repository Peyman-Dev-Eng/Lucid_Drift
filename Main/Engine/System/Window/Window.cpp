#include "Window.h"

LDDrift::Window::Window() {
    GLB_assert(glfwInit())
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    settings.title = "NONE";
    settings.width = 500;
    settings.height = 500;
    settings.CanResize = false;
    settings.FillColorScreen = {0.0f, 0.0f, 0.0f, 1.0f};
}

void LDDrift::Window::CreateWindow() {
    std::string FinalTile = settings.title;
    FinalTile += " ( Lucid-Drift )";
    screen = glfwCreateWindow(settings.width, settings.height, settings.title, nullptr, nullptr);
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
}

void LDDrift::Window::SetTitle(const char* title) {
    glfwSetWindowTitle(screen, title);
    settings.title = title;
}

void LDDrift::Window::SetSize(const int width, const int height) {
    glfwSetWindowSize(screen, width, height);
    settings.width = width;
    settings.height = height;
}

void LDDrift::Window::SetFillScreenColor(const LDDrift::VecCol& color) {
    settings.FillColorScreen = color;
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

LDDrift::VecCol LDDrift::Window::GetFillScreenColor() const {
    return settings.FillColorScreen;
}

LDDrift::VecPos2D LDDrift::Window::GetWindowSize() const {
    return LDDrift::VecPos2D{static_cast<float>(settings.width), static_cast<float>(settings.height)};
}

LDDrift::VecPos2D LDDrift::Window::GetPosition() const {
    return LDDrift::VecPos2D{static_cast<float>(settings.pos_x), static_cast<float>(settings.pos_y)};
}

LDDrift::Window::~Window() {
    this->DestroyWindow();
}
