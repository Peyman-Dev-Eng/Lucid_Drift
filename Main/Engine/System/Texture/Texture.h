#ifndef LUCID_DRIFT_TEXTURE_H
#define LUCID_DRIFT_TEXTURE_H
#include <vector>
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
        std::vector<float> textureData;
        float colorMulti = 1.0f;

    public: // functions
        Texture();
        ~Texture();
        void SetColorMultiplierForTexture(float _colorMultiplier);
        [[nodiscard]] float GetColorMultiplierOfTexture() const;
        bool operator!=(const Texture& tex) const;
        bool operator==(const Texture& tex) const;
        void SetTextureCoordinates(const std::vector<float>& _textureCoordinates);
        [[nodiscard]] const std::vector<float>& GetTextureCoordinates() const;
        void GenerateTexture();
        void LoadTexture() const;
        void FreeTexture() const;
        [[nodiscard]] GLuint GetTextureID() const;
    };
}

#endif
