#ifndef LUCID_DRIFT_TEXTURE_RENDER_H
#define LUCID_DRIFT_TEXTURE_RENDER_H
#include <System/Texture/Texture.h>
#include <set>
#include <algorithm>
namespace LDDrift
{
    class TextureRender
    {
    private: // functions
        void SetVertexShaderSource();
        void SetFragmentShaderSource();
        static GLuint Compile(GLenum type, const char* const shaderSource);

    private: // OpenGL
        const char* VertexShaderSource = "";
        const char* FragmentShaderSource = "";
        GLuint VAO = 0, VBO = 0;
        GLuint FragmentShader = 0;
        GLuint VertexShader = 0;
        GLuint program = 0;

    private: // to render
        std::set<LDDrift::Texture*> textures;

    public:
        TextureRender();
        ~TextureRender();
        void Initialize();
        void RemoveTexture(LDDrift::Texture* texture );
        void Render() const;
        void AddTexture(LDDrift::Texture* texture);
        void SendToGPU() const;
    };
}

#endif
