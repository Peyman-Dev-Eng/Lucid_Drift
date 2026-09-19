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
    float centerPixelX,
    float centerPixelY,
    float radiusPixels,
    int pointCount) {
    for (int i = 0; i < pointCount; ++i) {
        const float radians = 2.0f * std::numbers::pi_v<float> * i / pointCount;
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

    constexpr int pointCount = 90;
    constexpr float pixelRadius = 100;

    constexpr float centerNDC_X = 0;
    constexpr float centerNDC_Y = 0;

    constexpr float radiusNDC_X = pixelRadius / static_cast<float>(HALF_SCREEN_WIDTH);
    constexpr float radiusNDC_Y = pixelRadius / static_cast<float>(HALF_SCREEN_HEIGHT);

    constexpr int vertexCount = pointCount * 2 * 3;

    float circleVertices[pointCount * 3];

    initCircleVerticesPixels(circleVertices, HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, pixelRadius, pointCount);

    float lineCircleVertices[(vertexCount * 3)];
    float mainLine[18];
    float mainLine2[18];

    constexpr int lastPoint = (pointCount - 1) * 3;
    unsigned int forLoopCounter = 0;
    for (int vertex = 0; vertex < pointCount * 3; vertex += 3) {
        const float px = vertex == 0 ? circleVertices[lastPoint]     : circleVertices[vertex - 3];
        const float py = vertex == 0 ? circleVertices[lastPoint + 1] : circleVertices[vertex - 2];
        const float cx = circleVertices[vertex];
        const float cy = circleVertices[vertex + 1];

        std::vector<LDDrift::Actors::Line::PNT> triangles =
            LDDrift::Actors::Line(LDDrift::VecPos2D{px, py}, LDDrift::VecPos2D{cx, cy})
            .SetThickness(3).SetScreenSize(LDDrift::VecPos2D{SCREEN_WIDTH, SCREEN_HEIGHT})
            .CreateTriangles().GetPoints();
        lineCircleVertices[forLoopCounter++] = triangles[0].Point_1.X;
        lineCircleVertices[forLoopCounter++] = triangles[0].Point_1.Y;
        lineCircleVertices[forLoopCounter++] = 0.0f;
        lineCircleVertices[forLoopCounter++] = triangles[0].Point_2.X;
        lineCircleVertices[forLoopCounter++] = triangles[0].Point_2.Y;
        lineCircleVertices[forLoopCounter++] = 0.0f;
        lineCircleVertices[forLoopCounter++] = triangles[0].Point_3.X;
        lineCircleVertices[forLoopCounter++] = triangles[0].Point_3.Y;
        lineCircleVertices[forLoopCounter++] = 0.0f;
        lineCircleVertices[forLoopCounter++] = triangles[1].Point_1.X;
        lineCircleVertices[forLoopCounter++] = triangles[1].Point_1.Y;
        lineCircleVertices[forLoopCounter++] = 0.0f;
        lineCircleVertices[forLoopCounter++] = triangles[1].Point_2.X;
        lineCircleVertices[forLoopCounter++] = triangles[1].Point_2.Y;
        lineCircleVertices[forLoopCounter++] = 0.0f;
        lineCircleVertices[forLoopCounter++] = triangles[1].Point_3.X;
        lineCircleVertices[forLoopCounter++] = triangles[1].Point_3.Y;
        lineCircleVertices[forLoopCounter++] = 0.0f;
    }
    const GLuint vertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    const GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    const GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cout << "Link error: " << log << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO = 0, VBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(lineCircleVertices), lineCircleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
