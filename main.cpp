#include <iostream>
#include <thread>
#include "Main/Engine/System/Input/input.h"
#include "System/Window/Window.h"

static const char* VertexShader = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
static const char* FragmentShader = R"(
#version 460 core
out vec4 fragColor;
void main() {
    fragColor = vec4(1.0,0.0,0.0,1.0);
}
)";

static GLuint CompileShader(const GLenum type, const char* source) {
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

int main() {

    return 0;
}
