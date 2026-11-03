#include "TextureRender.h"
#include <System/Core/Core.h>

#include "Transform.h"

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
        "uniform mat4 U_VIEW_PROJECTION;\n"
        "void main() {\n"
        "    gl_Position = U_VIEW_PROJECTION * vec4(position, 0.0, 1.0);\n"
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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    const LDDrift::VecPos2D viewPortSize = core->window.GetViewportSize();
    glUseProgram(program);
    const GLint viewProjectionLocation = glGetUniformLocation(program, "U_VIEW_PROJECTION");
    const glm::mat4 viewProjection = core->camera.GetProjectionMatrix(viewPortSize.X, viewPortSize.Y) *
        core->camera.GetViewMatrix();
    glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, value_ptr(viewProjection));
}

void LDDrift::TextureRender::AddTexture(LDDrift::Texture* texture) {
    if (std::ranges::find(textures, texture) == textures.end()) {
        textures.push_back(texture);
        texture->GenerateTexture();
        const std::size_t textureDataSize = texture->GetTextureCoordinates().size() / 4;
        howToReadDataFromGPU.push_back(readDataFrom_GPU{.start = lastIndexForStart, .count = textureDataSize});
        lastIndexForStart += textureDataSize;
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
    if (const auto it = std::ranges::find(textures, texture);
        it != textures.end()) {
        textures.erase(it);
    }
}

void LDDrift::TextureRender::Render() const {
    const std::size_t howToReadDataFromGPU_SIZE = howToReadDataFromGPU.size();
    for (std::size_t texture = 0; texture < howToReadDataFromGPU_SIZE; ++texture) {
        glUseProgram(program);
        textures[texture]->LoadTexture();
        glUniform1i(glGetUniformLocation(program, "texture_S"), 0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN,
                     static_cast<int>(howToReadDataFromGPU[texture].start),
                     static_cast<int>(howToReadDataFromGPU[texture].count));
    }
}

void LDDrift::TextureRender::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::TextureRender::SetViewMatrix(const glm::mat4& u_viewProjectionMatrix) const {
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "U_VIEW_PROJECTION"), 1, GL_FALSE, value_ptr(u_viewProjectionMatrix));
}
