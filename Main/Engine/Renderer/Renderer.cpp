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
    WidthScreen(widthScreen), HeightScreen(heightScreen), indexOfFirstVertexInVertexArray(0) {
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

void LDDrift::Renderer::AddShapeToRender(const LDDrift::Actors::Shape* shape) {
    const std::vector<LDDrift::VecPos2D>& shapeVerticesAddress = shape->GetPoints();
    const std::vector<LDDrift::VecCol>& shapeVerticesColor = shape->GetColorOfPoints();
    const std::size_t vertexCount = shapeVerticesAddress.size();
    for (std::size_t vertex = 0; vertex < vertexCount; ++vertex) {
        vertices.push_back(shapeVerticesAddress[vertex].X);
        vertices.push_back(shapeVerticesAddress[vertex].Y);
        vertices.push_back(0.0f);
        vertices.push_back(shapeVerticesColor[vertex].R);
        vertices.push_back(shapeVerticesColor[vertex].G);
        vertices.push_back(shapeVerticesColor[vertex].B);
        vertices.push_back(shapeVerticesColor[vertex].A);
    }
    howToReadShapeData.push_back({
        .drawType = shape->IsHaveThickness() ? LUCID_DRIFT_SHAPE_RENDER_AS_OUTLINE : LUCID_DRIFT_SHAPE_RENDER_AS_FILLED,
        .startIndex = indexOfFirstVertexInVertexArray, .count = vertexCount
    });
    indexOfFirstVertexInVertexArray += vertexCount;
}

void LDDrift::Renderer::render() {
    const std::size_t howToReadShapeData_SIZE = howToReadShapeData.size();
    GLB_assert(howToReadShapeData_SIZE != 0)
    for (std::size_t shape = 0; shape < howToReadShapeData_SIZE; ++shape) {
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(howToReadShapeData[shape].drawType == LUCID_DRIFT_SHAPE_RENDER_AS_FILLED
                         ? GL_TRIANGLE_FAN
                         : GL_TRIANGLES,
                     static_cast<int>(howToReadShapeData[shape].startIndex),
                     static_cast<int>(howToReadShapeData[shape].count));
    }
}
