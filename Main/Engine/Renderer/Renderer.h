#ifndef LUCID_DRIFT_RENDERER_H
#define LUCID_DRIFT_RENDERER_H
#include "glad/glad.h"
#include <vector>
#include <ShapeData.h>
#include "Actors/Shapes/MainShape/Shape.h"
#define LUCID_DRIFT_SHAPE_RENDER_AS_FILLED 1
#define LUCID_DRIFT_SHAPE_RENDER_AS_OUTLINE 2

namespace LDDrift
{
    class Renderer final
    {
    private:
        struct ReadShapeVertices
        {
            int drawType;
            std::size_t startIndex;
            std::size_t count;
        };
    private: // opengl data
        std::vector<ReadShapeVertices> howToReadShapeData;
        std::vector<float> vertices;
        const char* VertexShaderSource{nullptr};
        const char* FragmentShaderSource{nullptr};
        GLuint VertexShader{}, FragmentShader{};
        GLuint VAO{0}, VBO{0};
        GLuint program{};

    private:
        int WidthScreen, HeightScreen;
        std::size_t indexOfFirstVertexInVertexArray;

    private: // functions
        void SetFragmentShaderSource();
        void SetVertexShaderSource();
        static GLuint Compile(GLenum type, const char* source);

    public:
        explicit Renderer(const int& widthScreen = 500 /* Width screen */, const int& heightScreen = 500 /* height screen */);
        void SetWidthScreen(int WS );
        void SetHeightScreen(int HS );
        [[nodiscard]] GLuint GetProgram() const;
        void AddShapeToRender(const LDDrift::Actors::Shape*);
        void render();
    };
}

#endif
