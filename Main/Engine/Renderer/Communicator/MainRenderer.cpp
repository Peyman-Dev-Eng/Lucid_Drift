// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#include "MainRenderer.h"
#include <System/Core/Core.h>

LDDrift::MainRenderer::MainRenderer() = default;

LDDrift::MainRenderer::~MainRenderer() = default;

void LDDrift::MainRenderer::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

glm::mat4 LDDrift::MainRenderer::UpdateViewMatrix() const {
    const LDDrift::VecPos2D viewPortSize = core->window.GetViewportSize();
    const glm::mat4 viewProjection =
        core->camera.GetProjectionMatrix(viewPortSize.X, viewPortSize.Y) * core->camera.GetViewMatrix();
    return viewProjection;
}

void LDDrift::MainRenderer::StaticDrawer(const LDDrift::Core* _core,
                                         const std::vector<LDDrift::Actors::Shape*>& shapes,
                                         const std::vector<LDDrift::Actors::Line*>& lines) {
    const char* const vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec4 aColor;

    uniform mat4 uViewProjection;

    out vec4 outColor;

    void main() {
        gl_Position = uViewProjection * vec4(aPos, 1.0);
        outColor = aColor;
    }
)";
    const char* const fragmentShaderSource = R"(
    #version 460 core
    in vec4 outColor;
    out vec4 fragColor;
    void main() {
        fragColor = outColor;
    }
)";
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    const GLuint program = glCreateProgram();

    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    const GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    // init uniform mat4 uViewProjection in Vertex shader source
    const LDDrift::VecPos2D viewPortSize = _core->window.GetViewportSize();
    glUseProgram(program);
    const GLint viewProjectionLocation = glGetUniformLocation(program, "uViewProjection");
    const glm::mat4 viewProjection = _core->camera.GetProjectionMatrix(viewPortSize.X, viewPortSize.Y) *
        _core->camera.GetViewMatrix();
    glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, value_ptr(viewProjection));

    std::vector<std::pair<std::size_t, std::size_t>> readDataFromGpu;
    std::vector<float> vertices;

    std::size_t lastIndex = 0;
    for (LDDrift::Actors::Shape* shape : shapes) {
        std::vector<float> triangles;
        if (shape->ShapeIsConcave()) {
            const LDDrift::Triangulation_S<LDDrift::ActorType::concave> triangulation(shape);
            triangles = triangulation.CreateTriangles();
        } else {
            const LDDrift::Triangulation_S<LDDrift::ActorType::convex> triangulation(shape);
            triangles = triangulation.CreateTriangles();
        }
        const std::size_t vertexCount = triangles.size() / 3;
        const std::vector<LDDrift::VecCol>& Colors = shape->GetColorOfPoints();
        for (std::size_t vertex = 0; vertex < vertexCount; ++vertex) {
            vertices.push_back(triangles[vertex * 3 + 0]);
            vertices.push_back(triangles[vertex * 3 + 1]);
            vertices.push_back(triangles[vertex * 3 + 2]);

            vertices.push_back(Colors[vertex % Colors.size()].R);
            vertices.push_back(Colors[vertex % Colors.size()].G);
            vertices.push_back(Colors[vertex % Colors.size()].B);
            vertices.push_back(Colors[vertex % Colors.size()].A);
        }

        readDataFromGpu.push_back({lastIndex, vertexCount});
        lastIndex += vertexCount;
    }
    for (const LDDrift::Actors::Line* line : lines) {
        const LDDrift::VecCol& color = line->GetColor();
        const std::vector<LDDrift::Actors::Line::PNT>& points = line->GetPoints();

        // point one | first triangle
        vertices.push_back(points[0].Point_1.X);
        vertices.push_back(points[0].Point_1.Y);
        vertices.push_back(0.0f);
        vertices.push_back(color.R);
        vertices.push_back(color.G);
        vertices.push_back(color.B);
        vertices.push_back(color.A);

        // point two | first triangle
        vertices.push_back(points[0].Point_2.X);
        vertices.push_back(points[0].Point_2.Y);
        vertices.push_back(0.0f);
        vertices.push_back(color.R);
        vertices.push_back(color.G);
        vertices.push_back(color.B);
        vertices.push_back(color.A);

        // point three | first triangle
        vertices.push_back(points[0].Point_3.X);
        vertices.push_back(points[0].Point_3.Y);
        vertices.push_back(0.0f);
        vertices.push_back(color.R);
        vertices.push_back(color.G);
        vertices.push_back(color.B);
        vertices.push_back(color.A);

        // point one | second triangle
        vertices.push_back(points[1].Point_1.X);
        vertices.push_back(points[1].Point_1.Y);
        vertices.push_back(0.0f);
        vertices.push_back(color.R);
        vertices.push_back(color.G);
        vertices.push_back(color.B);
        vertices.push_back(color.A);

        // point two | second triangle
        vertices.push_back(points[1].Point_2.X);
        vertices.push_back(points[1].Point_2.Y);
        vertices.push_back(0.0f);
        vertices.push_back(color.R);
        vertices.push_back(color.G);
        vertices.push_back(color.B);
        vertices.push_back(color.A);

        // point three | second triangle
        vertices.push_back(points[1].Point_3.X);
        vertices.push_back(points[1].Point_3.Y);
        vertices.push_back(0.0f);
        vertices.push_back(color.R);
        vertices.push_back(color.G);
        vertices.push_back(color.B);
        vertices.push_back(color.A);

        readDataFromGpu.push_back({lastIndex, 6});
        lastIndex += 6; // 6 -> vertex count
    }

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(float)), vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    if (const std::size_t readDataSize = readDataFromGpu.size();
        readDataSize != 0) {
        glUseProgram(program);
        for (std::size_t vertex = 0; vertex < readDataSize; ++vertex) {
            glDrawArrays(GL_TRIANGLES, readDataFromGpu[vertex].first, readDataFromGpu[vertex].second);
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);
}

void LDDrift::MainRenderer::StaticDrawer(const LDDrift::Core* _core, const std::vector<LDDrift::Texture*>& textures) {
    const char* const vertShaderSrc =
        "#version 460 core\n"
        "layout (location = 0) in vec2 position;\n"
        "layout (location = 1) in vec2 texCoord;\n"
        "out vec2 outColor;\n"
        "uniform mat4 U_VIEW_PROJECTION;\n"
        "void main() {\n"
        "    gl_Position = U_VIEW_PROJECTION * vec4(position, 0.0, 1.0);\n"
        "    outColor = texCoord;\n"
        "}";
    const char* const fragShaderSrc =
        "#version 460 core\n"
        "in vec2 outColor;\n"
        "uniform sampler2D texture_S;\n"
        "out vec4 fragColor;\n"
        "uniform float colorMultiplier;\n"
        "void main() {\n"
        "    vec4 texColor = texture(texture_S, outColor);\n"
        "    fragColor = vec4(texColor.rgb * colorMultiplier, texColor.a);\n"
        "}";

    GLuint VAO = 0, VBO = 0;
    const GLuint program = glCreateProgram();

    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderSrc, nullptr);
    glCompileShader(vertexShader);

    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(program);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    const LDDrift::VecPos2D viewPortSize = _core->window.GetViewportSize();
    const GLint viewProjectionLocation = glGetUniformLocation(program, "U_VIEW_PROJECTION");
    const glm::mat4 viewProjection = _core->camera.GetProjectionMatrix(viewPortSize.X, viewPortSize.Y) *
        _core->camera.GetViewMatrix();
    glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, value_ptr(viewProjection));

    std::vector<std::pair<std::size_t, std::size_t>> readDataFromGpu;

    std::size_t counter = 0;
    for (const LDDrift::Texture* texture : textures) {
        std::size_t textureSize = texture->GetTextureCoordinates().size() / 4;
        readDataFromGpu.push_back({counter, textureSize});
        counter += textureSize;
    }
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

    const std::size_t SIZE = readDataFromGpu.size();
    for (std::size_t texture = 0; texture < SIZE; ++texture) {
        glUseProgram(program);
        textures[texture]->LoadTexture();
        glUniform1f(glGetUniformLocation(program, "colorMultiplier"),
                    std::clamp(textures[texture]->GetColorMultiplierOfTexture(), 0.0f, 1.0f));
        glUniform1i(glGetUniformLocation(program, "texture_S"), 0);
        glDrawArrays(GL_TRIANGLE_FAN,
                     static_cast<int>(readDataFromGpu[texture].first),
                     static_cast<int>(readDataFromGpu[texture].second));
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);
}
