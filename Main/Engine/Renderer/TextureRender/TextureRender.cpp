// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#include "TextureRender.h"
#include <System/Core/Core.h>

#include "Transformer.h"

LDDrift::TextureRender::TextureRender() = default;

LDDrift::TextureRender::~TextureRender() = default;

GLuint LDDrift::TextureRender::Compile(const GLenum type, const char* const shaderSource) {
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    GLint ShaderCompileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ShaderCompileStatus);
    if (ShaderCompileStatus == GL_FALSE) {
        GLint InfoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
        char InfoLog[InfoLogLength];
        glGetShaderInfoLog(shader, InfoLogLength, &InfoLogLength, InfoLog);
        throw LDDrift::Except("OpenGL", "TextureRender", std::string(InfoLog));
    }
    return shader;
}

bool LDDrift::TextureRender::findTexture(const LDDrift::Actors::Texture* texture) const {
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

    try {
        VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
    } catch (const LDDrift::Except& e) {
        LDDrift::Logger::ErrorLog(e.program, e.ErrorFromLocation,
                                  Log(e.message, LDDrift::LogType::CompileOpenGLShaderSourceFailed));
        char yesOrNo = '.';
        while (yesOrNo != 'y' && yesOrNo != 'Y' && yesOrNo != 'n' && yesOrNo != 'N') {
            std::cerr <<
                "Do you want to continue? (Under these conditions, the rendering system might not function correctly or as you intend.) (y/n): ";
            std::cin >> yesOrNo;
            if (yesOrNo == 'n' || yesOrNo == 'N') {
                std::cerr << "we are sorry!" << std::endl;
                exit(-1);
            }
        }
    }

    try {
        FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);
    } catch (const LDDrift::Except& e) {
        LDDrift::Logger::ErrorLog(e.program, e.ErrorFromLocation,
                                  Log(e.message, LDDrift::LogType::CompileOpenGLShaderSourceFailed));
        char yesOrNo = '.';
        while (yesOrNo != 'y' && yesOrNo != 'Y' && yesOrNo != 'n' && yesOrNo != 'N') {
            std::cerr <<
                "Do you want to continue? (Under these conditions, the rendering system might not function correctly or as you intend.) (y/n): ";
            std::cin >> yesOrNo;
            if (yesOrNo == 'n' || yesOrNo == 'N') {
                std::cerr << "we are sorry!" << std::endl;
                exit(-1);
            }
        }
    }
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
        throw LDDrift::Except("OpenGL", "TextureRender", std::string(InfoLog));
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

void LDDrift::TextureRender::AddTexture(LDDrift::Actors::Texture* texture, const int& use_UVP) {
    if (!findTexture(texture)) {
        textures.push_back({.use_U_VIEW_PROJECTION = use_UVP, .texture = texture});
        const std::size_t textureDataSize = texture->GetTextureCoordinates().size() / 4;
        howToReadDataFromGPU.push_back(readDataFrom_GPU{.start = lastIndexForStart, .count = textureDataSize});
        lastIndexForStart += textureDataSize;
    }
}

void LDDrift::TextureRender::SendToGPU() {
    std::pmr::vector<float> vertices;
    for (const auto [use_U_VIEW_PROJECTION, texture] : textures) {
        vertices.insert(vertices.end(), texture->GetTextureCoordinates().begin(),
                        texture->GetTextureCoordinates().end());
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

void LDDrift::TextureRender::RemoveTexture(const LDDrift::Actors::Texture* texture) {
    for (std::size_t Index = 0; Index < textures.size(); ++Index) {
        if (textures[Index].texture == texture) {
            textures.erase(textures.begin() + Index);
            howToReadDataFromGPU.erase(howToReadDataFromGPU.begin() + Index);
            ReloadHowToReadDataFromGPU();
            break;
        }
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

void LDDrift::TextureRender::ReloadFromTextures() {
    lastIndexForStart = 0;
    howToReadDataFromGPU.clear();
    for (const auto& [useViewProjection, texture] : textures) {
        const std::size_t textureSize = texture->GetTextureCoordinates().size() / 4;
        howToReadDataFromGPU.push_back({.start = lastIndexForStart, .count = textureSize});
        lastIndexForStart += textureSize;
    }
}

void LDDrift::TextureRender::ReloadHowToReadDataFromGPU() {
    constexpr int firstIndex = 0;
    howToReadDataFromGPU[firstIndex].start = 0;
    const std::size_t howToReadDataFromGPU_SIZE = howToReadDataFromGPU.size();
    for (std::size_t index = 1; index < howToReadDataFromGPU_SIZE; ++index) {
        howToReadDataFromGPU[index].start = (howToReadDataFromGPU[index - 1].start +
            howToReadDataFromGPU[index - 1].count);
    }
}
