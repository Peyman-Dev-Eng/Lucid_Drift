#include "Renderer.h"

void LDDrift::Renderer::SetVertexShaderSource() {
    VertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 uTransform;
uniform mat4 uProjection;

out vec4 outColor;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0) * uTransform * uProjection;
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

LDDrift::Renderer::Renderer() : WidthScreen(500), HeightScreen(500) {
    this->SetVertexShaderSource();
    this->SetFragmentShaderSource();
    VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    program = glCreateProgram();
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    glLinkProgram(program);
}

LDDrift::Renderer::Renderer(const int WS, const int HS) : WidthScreen(WS), HeightScreen(HS) {
    this->SetVertexShaderSource();
    this->SetFragmentShaderSource();
    VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    program = glCreateProgram();
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    glLinkProgram(program);
}

GLuint LDDrift::Renderer::GetProgram() const {
    return program;
}


LDDrift::Renderer::~Renderer() = default;
