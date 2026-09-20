#ifndef LUCID_DRIFT_RENDERER_H
#define LUCID_DRIFT_RENDERER_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "glad/glad.h"
#include <vector>
#include <ShapeData.h>
#include "Actors/Shapes/MainShape/Shape.h"

namespace LDDrift
{
    class Renderer final
    {
    private:
        std::vector<ShapeData> Shapes;
        const char* VertexShaderSource{nullptr};
        const char* FragmentShaderSource{nullptr};
        GLuint VertexShader{}, FragmentShader{};
        GLuint VAO{0}, VBO{0};
        GLuint program{};

    private:
        int WidthScreen, HeightScreen;

    private: // functions
        void SetFragmentShaderSource();
        void SetVertexShaderSource();
        static GLuint Compile(GLenum type, const char* source);

    public:
        explicit Renderer(const int& widthScreen = 500 /* Width screen */, const int& heightScreen = 500 /* height screen */);
        void SetWidthScreen(int WS );
        void SetHeightScreen(int HS );
        [[nodiscard]] GLuint GetProgram() const;
        ShapeData GetShapeData(const LDDrift::Actors::Shape*) const;
    };
}

#endif
