#include "Renderer.h"

void LDDrift::Renderer::SetVertexShaderSource() {
    VertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 outColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    outColor = aColor;
}
)";
}

void LDDrift::Renderer::SetFragmentShaderSource() {
    FragmentShaderSource = R"(
#version 460 core
in vec4 outColor;
out vec4 fragColor;
void main() {
    fragColor = outColor;
}
)";
}

GLuint LDDrift::Renderer::Compile(const GLenum type, const char* source) {
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

LDDrift::Renderer::Renderer(const int& widthScreen, const int& heightScreen) : WidthScreen(widthScreen), HeightScreen(heightScreen) {
    this->SetVertexShaderSource();
    this->SetFragmentShaderSource();
    VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    program = glCreateProgram();
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    glLinkProgram(program);

    // create vbo buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // create vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


}

GLuint LDDrift::Renderer::GetProgram() const {
    return program;
}

void LDDrift::Renderer::SetWidthScreen(const int WS) {
    WidthScreen = WS;
}

void LDDrift::Renderer::SetHeightScreen(const int HS) {
    HeightScreen = HS;
}

LDDrift::ShapeData LDDrift::Renderer::GetShapeData(const LDDrift::Actors::Shape* shape) const {
    LDDrift::ShapeData shape_data;
    const int HalfWidthScreen = WidthScreen / 2;
    const int HalfHeightScreen = HeightScreen / 2;
    for (std::size_t point = 0; point < shape->GetPointCount(); ++point) {
        const float XinOpenGLCoordinateSystem = ((shape->GetPoint(point).X - static_cast<float>(HalfWidthScreen)) /
            static_cast<float>(HalfWidthScreen));
        const float YinCoordinateSystem = ((shape->GetPoint(point).Y - static_cast<float>(HalfHeightScreen)) /
            static_cast<float>(HalfHeightScreen));
        shape_data.Vertices.push_back(LDDrift::VecPos2D{XinOpenGLCoordinateSystem, YinCoordinateSystem, 0.0f});
        shape_data.PointsColors.push_back(shape->GetPointColor(point));
    }
    return shape_data;
}

