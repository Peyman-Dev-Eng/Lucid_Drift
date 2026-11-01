#include "TextureRender.h"

LDDrift::TextureRender::TextureRender() = default;

LDDrift::TextureRender::~TextureRender() = default;

GLuint LDDrift::TextureRender::Compile(const GLenum type, const char* const shaderSource) {
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    return shader;
}

void LDDrift::TextureRender::SetVertexShaderSource() {
    VertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec2 position;\n"
        "layout (location = 1) in vec2 texCoord;\n"
        "out vec2 outColor;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 0.0, 1.0);\n"
        "    outColor = texCoord;\n"
        "}";
}

void LDDrift::TextureRender::SetFragmentShaderSource() {
    FragmentShaderSource =
        "#version 460 core\n"
        "in vec2 outColor;\n"
        "uniform sampler2D texture_S;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = texture(texture_S, outColor);\n"
        "}";
}

void LDDrift::TextureRender::Initialize() {
    SetVertexShaderSource();
    SetFragmentShaderSource();

    FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    program = glCreateProgram();
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    glLinkProgram(program);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void LDDrift::TextureRender::AddTexture(LDDrift::Texture* texture) {
    if (!textures.contains(texture)) {
        textures.insert(texture);
        texture->GenerateTexture();
    }
}

void LDDrift::TextureRender::SendToGPU() const {
    std::vector<float> vertices;
    for (const LDDrift::Texture* tex : textures) {
        vertices.insert(vertices.end(), tex->GetTextureCoordinates().begin(), tex->GetTextureCoordinates().end());
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(float)), vertices.data(),
                 GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void LDDrift::TextureRender::RemoveTexture(LDDrift::Texture* texture) {
    if (textures.contains(texture)) {
        textures.erase(texture);
    }
}

void LDDrift::TextureRender::Render() const {
    for (const LDDrift::Texture* tex : textures) {
        glUseProgram(program);
        tex->LoadTexture();
        glUniform1i(glGetUniformLocation(program, "texture_S"), 0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
