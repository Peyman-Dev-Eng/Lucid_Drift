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

static void SetToVertices(float* vertices, const std::vector<LDDrift::Actors::Line::PNT>& points, const uint size) {
    static uint LastIndex = 0;
    vertices[LastIndex] = points[0].Point_1.X;
    vertices[LastIndex + 1] = points[0].Point_1.Y;
    vertices[LastIndex + 2] = 0.0f;
    LastIndex += 3;
    vertices[LastIndex] = points[0].Point_2.X;
    vertices[LastIndex + 1] = points[0].Point_2.Y;
    vertices[LastIndex + 2] = 0.0f;
    LastIndex += 3;
    vertices[LastIndex] = points[0].Point_3.X;
    vertices[LastIndex + 1] = points[0].Point_3.Y;
    vertices[LastIndex + 2] = 0.0f;
    LastIndex += 3;
    vertices[LastIndex] = points[1].Point_1.X;
    vertices[LastIndex + 1] = points[1].Point_1.Y;
    vertices[LastIndex + 2] = 0.0f;
    LastIndex += 3;
    vertices[LastIndex] = points[1].Point_2.X;
    vertices[LastIndex + 1] = points[1].Point_2.Y;
    vertices[LastIndex + 2] = 0.0f;
    LastIndex += 3;
    vertices[LastIndex] = points[1].Point_3.X;
    vertices[LastIndex + 1] = points[1].Point_3.Y;
    vertices[LastIndex + 2] = 0.0f;
    LastIndex %= size;
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

    constexpr int pointCount = 45;

    constexpr int angleRadian = 360 / pointCount;
    constexpr int vertexCount = pointCount * 2 * 3;

    constexpr float centerX = static_cast<float>((HALF_SCREEN_WIDTH - HALF_SCREEN_WIDTH)) / HALF_SCREEN_WIDTH;
    constexpr float centerY = static_cast<float>((HALF_SCREEN_HEIGHT - HALF_SCREEN_HEIGHT)) / HALF_SCREEN_HEIGHT;

    constexpr float RadiusX = 40.0f / HALF_SCREEN_WIDTH;
    constexpr float RadiusY = 40.0f / HALF_SCREEN_HEIGHT;


    float circlePoints[pointCount * 3];

    int circlePointsIndex = 0;
    for (int angle = 0; angle < 360; angle += angleRadian) {
        const float radians = static_cast<float>(angle) * std::numbers::pi_v<float> / 180;
        const float targetX = centerX + RadiusX * std::cos(radians);
        const float targetY = centerY + RadiusY * std::sin(radians);
        circlePoints[circlePointsIndex++] = targetX;
        circlePoints[circlePointsIndex++] = targetY;
        circlePoints[circlePointsIndex++] = 0.0f;
    }

    const GLuint vertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    const GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    const GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO = 0, VBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(circlePoints), circlePoints, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, pointCount);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
