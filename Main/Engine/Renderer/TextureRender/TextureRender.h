#ifndef LUCID_DRIFT_TEXTURE_RENDER_H
#define LUCID_DRIFT_TEXTURE_RENDER_H
#include <Actors/Texture/Texture.h>
#include <set>
#include <algorithm>
#include <VecPos2D.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LDDrift
{
    class Core;

    class TextureRender final
    {
    private: // functions
        bool findTexture(const LDDrift::Texture* texture) const;
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
        struct TEXTURE
        {
            int use_U_VIEW_PROJECTION;
            LDDrift::Texture* texture;
        };

        LDDrift::Core* core = nullptr;
        std::vector<TEXTURE> textures;

    public:
        TextureRender();
        ~TextureRender();
        void DeleteTextures();
        void SetColorMultiplier(float colorMultiplier) const;
        void SetCorePTR(LDDrift::Core* core_ptr);
        void Initialize();
        void RemoveTexture(LDDrift::Texture* texture);
        void Render() const;
        void AddTexture(LDDrift::Texture* texture, const int& use_UVP);
        void SendToGPU();
        void SetViewMatrix(const glm::mat4& u_viewProjectionMatrix) const;
    };
}

#endif
