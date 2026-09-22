#include <iostream>
#include <thread>
#include <Angle.h>
#include <glad/glad.h>
#include <VecPos.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <oneapi/tbb/task_group.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define HALF_SCREEN_WIDTH 640
#define HALF_SCREEN_HEIGHT 360

#include "Actors/Line/Line.h"
#include "Actors/Shapes/Circle/CircleShape.h"

static const char* VertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
static const char* FragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
)";

static GLuint Compile(const GLenum type, const char* source) {
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

static void initCircleVerticesPixels(
    float* circleVertices,
    const float centerPixelX,
    const float centerPixelY,
    const float radiusPixels,
    const int pointCount) {
    for (int i = 0; i < pointCount; ++i) {
        const float radians = 2.0f * std::numbers::pi_v<float> * static_cast<float>(i) / static_cast<float>(pointCount);
        circleVertices[i * 3 + 0] = centerPixelX + radiusPixels * std::cos(radians);
        circleVertices[i * 3 + 1] = centerPixelY + radiusPixels * std::sin(radians);
        circleVertices[i * 3 + 2] = 0.0f;
    }
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW." << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TEST", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
