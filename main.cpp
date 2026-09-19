#include <iostream>
#include <thread>
#include <Angle.h>
#include <glad/glad.h>
#include <VecPos.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <oneapi/tbb/task_group.h>

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
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
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
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1200, 900, "OpenGl", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    std::cout << "OpenGL: "
          << glGetString(GL_VERSION)
          << '\n';
    int width = 1200, height = 900;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glDisable(GL_CULL_FACE);
    const GLuint VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    const GLuint FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    const GLuint program = glCreateProgram();
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    glLinkProgram(program);
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    std::cout << "Program linked: "
              << linked
              << '\n';

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    constexpr int PointCount = 45;

    float vertices[PointCount * 3];

    constexpr float VertexAngle =
        360.0f / PointCount;

    uint pointIndex = 0;

    for (float angle = 0.0f;
         angle < 360.0f;
         angle += VertexAngle, pointIndex += 3) {
        constexpr float Radius = 0.5f;
        constexpr float CenterX = 0.0f;
        constexpr float CenterY = 0.0f;

        const float radians =
            angle * std::numbers::pi_v<float> / 180.0f;

        vertices[pointIndex] =
            CenterX + Radius * std::cos(radians);

        vertices[pointIndex + 1] =
            CenterY + Radius * std::sin(radians);

        vertices[pointIndex + 2] = 0.0f;
    }
    float points[810];
    for (uint point = 0; point < PointCount; ++point) {
        const uint PreviousIndex = point == 0 ? (PointCount - 1) * 3 : (point - 1) * 3;
        const uint CurrentIndex = point * 3;
        std::vector<LDDrift::Actors::Line::PNT> PNTS = LDDrift::Actors::Line(
                                                           LDDrift::VecPos2D{
                                                               vertices[PreviousIndex], vertices[PreviousIndex + 1]
                                                           },
                                                           LDDrift::VecPos2D{
                                                               vertices[CurrentIndex], vertices[CurrentIndex + 1]
                                                           })
                                                       .SetScreenSize(LDDrift::VecPos2D{1200, 900})
                                                       .SetThickness(0.01f).CreateTriangles().GetPoints();
        for (const auto& p : PNTS) {
            std::cout
    << "P1: "
    << p.Point_1.X << ", "
    << p.Point_1.Y << '\n';

            std::cout
                << "P2: "
                << p.Point_2.X << ", "
                << p.Point_2.Y << '\n';

            std::cout
                << "P3: "
                << p.Point_3.X << ", "
                << p.Point_3.Y << '\n';

            std::cout << "----------------\n";
        }
        SetToVertices(points, PNTS, sizeof(points) / sizeof(float));
    }
    for (int i = 0; i < 18; i += 3) {
        std::cout
            << points[i] << ", "
            << points[i + 1] << ", "
            << points[i + 2] << '\n';
    }
    GLuint VAO = 0, VBO = 0;
    glGenVertexArrays(
        1
        ,
        &
        VAO
    );
    glGenBuffers(
        1
        ,
        &
        VBO
    );
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER

                 ,
                 VBO
    );
    glBufferData(GL_ARRAY_BUFFER

                 ,
                 sizeof
                 (points), points, GL_STATIC_DRAW

    );
    glEnableVertexAttribArray(
        0
    );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glBindVertexArray(0);
    while
    (
        !
        glfwWindowShouldClose(window)
    ) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 270);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return
        0;
}
