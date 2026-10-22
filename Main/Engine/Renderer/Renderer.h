#ifndef LUCID_DRIFT_RENDERER_H
#define LUCID_DRIFT_RENDERER_H
#include "glad/glad.h"
#include <vector>
#include <ShapeData.h>
#include <Actors/Line/Line.h>
#include <glm/gtc/type_ptr.hpp>
#include <set>
#include <System/Triangulation/Triangulation.h>
#define LUCID_DRIFT_SHAPE_RENDER_AS_FILLED 1
#define LUCID_DRIFT_SHAPE_RENDER_AS_OUTLINE 2

namespace LDDrift
{
    namespace Actors
    {
        class Shape;
    }

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
        LDDrift::Core* core;
        std::set<LDDrift::Actors::Line*> linePTRs;
        std::set<LDDrift::Actors::Shape*> shapePTRs;
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
        explicit Renderer(const int& widthScreen = 500 /* Width screen */,
                          const int& heightScreen = 500 /* height screen */);
        void Initialize();
        void SetCorePTR(LDDrift::Core* corePTR);
        void RebuildShapes();
        void SetWidthScreen(int WS);
        void SetHeightScreen(int HS);
        [[nodiscard]] GLuint GetProgram() const;
        void SendDataToGPU() const;
        void AddShapeToRender(LDDrift::Actors::Shape*);
        void AddLineToRender(LDDrift::Actors::Line*);
        void RemoveLineFromRender(LDDrift::Actors::Line*);
        void RemoveShapeFromRender(LDDrift::Actors::Shape*);
        void UpdateShapeData();
        void UpdateViewMatrix() const;
        void render() const;
    };
}

#endif
