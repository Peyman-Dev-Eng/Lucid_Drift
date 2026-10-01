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

LDDrift::Renderer::Renderer(const int& widthScreen, const int& heightScreen) :
    WidthScreen(widthScreen), HeightScreen(heightScreen), indexOfFirstVertexInVertexArray(0) {}

GLuint LDDrift::Renderer::GetProgram() const {
    return program;
}

void LDDrift::Renderer::SetWidthScreen(const int WS) {
    WidthScreen = WS;
}

void LDDrift::Renderer::SetHeightScreen(const int HS) {
    HeightScreen = HS;
}

void LDDrift::Renderer::Initialize() {
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

void LDDrift::Renderer::AddShapeToRender(LDDrift::Actors::Shape* shape) {
    shapePTRs.push_back(shape);
    const std::vector<LDDrift::VecCol>& vertexColor = shape->GetColorOfPoints();
    std::vector<float> VTC = {};
    const LDDrift::Triangulation<LDDrift::ActorType::convex> triangulation(shape);
    VTC = triangulation.CreateTriangles();
    const std::size_t vertexCount = VTC.size() / 3;
    for (std::size_t vertex = 0; vertex < vertexCount; ++vertex) {
        vertices.push_back(VTC[vertex * 3]);
        vertices.push_back(VTC[vertex * 3 + 1]);
        vertices.push_back(VTC[vertex * 3 + 2]);

        vertices.push_back(vertexColor[vertex % vertexColor.size()].R);
        vertices.push_back(vertexColor[vertex % vertexColor.size()].G);
        vertices.push_back(vertexColor[vertex % vertexColor.size()].B);
        vertices.push_back(vertexColor[vertex % vertexColor.size()].A);
    }
    howToReadShapeData.push_back({
        .drawType = shape->IsHaveThickness() ? LUCID_DRIFT_SHAPE_RENDER_AS_OUTLINE : LUCID_DRIFT_SHAPE_RENDER_AS_FILLED,
        .startIndex = indexOfFirstVertexInVertexArray, .count = vertexCount
    });
    indexOfFirstVertexInVertexArray += vertexCount;
}

void LDDrift::Renderer::SendDataToGPU() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void LDDrift::Renderer::UpdateShapeData() {
    vertices.clear();
    howToReadShapeData.clear();
    indexOfFirstVertexInVertexArray = 0;
    for (const auto& shape : shapePTRs) {
        const std::vector<LDDrift::VecCol>& vertexColor = shape->GetColorOfPoints();
        std::vector<float> VTC = {};
        const LDDrift::Triangulation<LDDrift::ActorType::convex> triangulation(shape);
        VTC = triangulation.CreateTriangles();
        const std::size_t vertexCount = VTC.size() / 3;
        for (std::size_t vertex = 0; vertex < vertexCount; ++vertex) {
            vertices.push_back(VTC[vertex * 3]);
            vertices.push_back(VTC[vertex * 3 + 1]);
            vertices.push_back(VTC[vertex * 3 + 2]);

            vertices.push_back(vertexColor[vertex % vertexColor.size()].R);
            vertices.push_back(vertexColor[vertex % vertexColor.size()].G);
            vertices.push_back(vertexColor[vertex % vertexColor.size()].B);
            vertices.push_back(vertexColor[vertex % vertexColor.size()].A);
        }
        howToReadShapeData.push_back({
            .drawType = shape->IsHaveThickness()
                            ? LUCID_DRIFT_SHAPE_RENDER_AS_OUTLINE
                            : LUCID_DRIFT_SHAPE_RENDER_AS_FILLED,
            .startIndex = indexOfFirstVertexInVertexArray, .count = vertexCount
        });
        indexOfFirstVertexInVertexArray += vertexCount;
    }
}

void LDDrift::Renderer::render() const {
    const std::size_t howToReadShapeData_SIZE = howToReadShapeData.size();
    if (howToReadShapeData_SIZE == 0) {
        return;
    }
    for (std::size_t shape = 0; shape < howToReadShapeData_SIZE; ++shape) {
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,
                     static_cast<int>(howToReadShapeData[shape].startIndex),
                     static_cast<int>(howToReadShapeData[shape].count));
    }
}

void LDDrift::Renderer::RebuildShapes() {
    for (LDDrift::Actors::Shape* shape : shapePTRs) {
        shape->Rebuild(WidthScreen, HeightScreen);
    }
    this->UpdateShapeData();
    this->SendDataToGPU();
}
