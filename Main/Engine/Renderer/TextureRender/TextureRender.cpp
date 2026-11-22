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

bool LDDrift::TextureRender::findTexture(const LDDrift::Texture* texture) const {
    for (const auto [use_U_VIEW_PROJECTION, _texture] : textures) {
        if (_texture == texture) {
            return true;
        }
    }
    return false;
}

void LDDrift::TextureRender::SetVertexShaderSource() {
    VertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec2 position;\n"
        "layout (location = 1) in vec2 texCoord;\n"
        "out vec2 outColor;\n"
        "uniform int use_VIEW_PROJECTION;\n" // 0 = false | 1 = true
        "uniform mat4 U_VIEW_PROJECTION;\n"
        "void main() {\n"
        "    if (use_VIEW_PROJECTION == 1) {\n"
        "        gl_Position = U_VIEW_PROJECTION * vec4(position, 0.0, 1.0);\n"
        "    } else {\n"
        "        gl_Position = vec4(position, 0.0, 1.0);\n"
        "    }"
        "    outColor = texCoord;\n"
        "}";
}

void LDDrift::TextureRender::SetFragmentShaderSource() {
    FragmentShaderSource =
        "#version 460 core\n"
        "in vec2 outColor;\n"
        "uniform sampler2D texture_S;\n"
        "out vec4 fragColor;\n"
        "uniform float colorMultiplier;\n"
        "void main() {\n"
        "    vec4 texColor = texture(texture_S, outColor);\n"
        "    fragColor = vec4(texColor.rgb * colorMultiplier, texColor.a);\n"
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
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    GLint ProgramLinkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &ProgramLinkStatus);

    if (ProgramLinkStatus == GL_FALSE) {
        GLint InfoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        char InfoLog[InfoLogLength];
        glGetProgramInfoLog(program, InfoLogLength, &InfoLogLength, InfoLog);
        throw std::runtime_error("link program failed: " + std::string(InfoLog));
    }


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

void LDDrift::TextureRender::AddTexture(LDDrift::Texture* texture, const int& use_UVP) {
    if (!findTexture(texture)) {
        textures.push_back({use_UVP, texture});
        texture->GenerateTexture();
        const std::size_t textureDataSize = texture->GetTextureCoordinates().size() / 4;
        howToReadDataFromGPU.push_back(readDataFrom_GPU{.start = lastIndexForStart, .count = textureDataSize});
        lastIndexForStart += textureDataSize;
    }
}

void LDDrift::TextureRender::SendToGPU() {
    lastIndexForStart = 0;
    howToReadDataFromGPU.clear();
    std::vector<float> vertices;
    for (const TEXTURE tex : textures) {
        const std::size_t textureSize = tex.texture->GetTextureCoordinates().size() / 4;
        howToReadDataFromGPU.push_back({.start = lastIndexForStart, .count = textureSize});
        lastIndexForStart += textureSize;
        vertices.insert(vertices.end(), tex.texture->GetTextureCoordinates().begin(), tex.texture->GetTextureCoordinates().end());
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
    if (const auto it = std::ranges::find(textures, texture, &TEXTURE::texture);
        it != textures.end()) {
        textures.erase(it);
    }
}

void LDDrift::TextureRender::Render() const {
    const std::size_t howToReadDataFromGPU_SIZE = howToReadDataFromGPU.size();
    for (std::size_t _texture = 0; _texture < howToReadDataFromGPU_SIZE; ++_texture) {
        glUseProgram(program);
        textures[_texture].texture->LoadTexture();
        SetColorMultiplier(textures[_texture].texture->GetColorMultiplierOfTexture());
        glUniform1i(glGetUniformLocation(program, "texture_S"), 0);
        glUniform1i(glGetUniformLocation(program, "use_VIEW_PROJECTION"), textures[_texture].use_U_VIEW_PROJECTION);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN,
                     static_cast<int>(howToReadDataFromGPU[_texture].start),
                     static_cast<int>(howToReadDataFromGPU[_texture].count));
    }
}

void LDDrift::TextureRender::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::TextureRender::SetViewMatrix(const glm::mat4& u_viewProjectionMatrix) const {
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "U_VIEW_PROJECTION"), 1, GL_FALSE,
                       value_ptr(u_viewProjectionMatrix));
}

void LDDrift::TextureRender::SetColorMultiplier(const float colorMultiplier) const {
    glUseProgram(program);
    glUniform1f(glGetUniformLocation(program, "colorMultiplier"), std::clamp(colorMultiplier, 0.0f, 1.0f));
}

void LDDrift::TextureRender::DeleteTextures() {
    textures.clear();
    howToReadDataFromGPU.clear();
    lastIndexForStart = 0;
    SendToGPU();
}
