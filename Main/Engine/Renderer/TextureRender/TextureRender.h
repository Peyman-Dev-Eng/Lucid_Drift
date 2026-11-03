#ifndef LUCID_DRIFT_TEXTURE_RENDER_H
#define LUCID_DRIFT_TEXTURE_RENDER_H
#include <System/Texture/Texture.h>
#include <set>
#include <algorithm>
#include <VecPos.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LDDrift
{
    class Core;
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

        struct readDataFrom_GPU
        {
            std::size_t start;
            std::size_t count;
        };

        std::vector<readDataFrom_GPU> howToReadDataFromGPU;
        std::size_t lastIndexForStart = 0; // save last index for set next start index of texture

    private: // to render
        LDDrift::Core* core = nullptr;
        std::vector<LDDrift::Texture*> textures;

    public:
        TextureRender();
        ~TextureRender();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void Initialize();
        void RemoveTexture(LDDrift::Texture* texture);
        void Render() const;
        void AddTexture(LDDrift::Texture* texture);
        void SendToGPU() const;
        void SetViewMatrix(const glm::mat4& u_viewProjectionMatrix) const;
    };
}

#endif
