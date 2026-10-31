#ifndef LUCID_DRIFT_TEXTURE_H
#define LUCID_DRIFT_TEXTURE_H
#include <ImageReader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LDDrift
{
    class Texture final
    {
    private:
        GLuint textureID = 0;

    public: // variables
        LDDrift::ImageReader image_reader;

    public: // functions
        Texture();
        ~Texture();
        void GenerateTexture();
        void LoadTexture();
        [[nodiscard]] GLuint GetTextureID() const;
    };
}

#endif
