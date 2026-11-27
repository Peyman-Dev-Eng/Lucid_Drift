// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#ifndef LUCID_DRIFT_TEXTURE_H
#define LUCID_DRIFT_TEXTURE_H
#include <vector>
#include <ImageReader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LDDrift::Actors
{
    class Texture final
    {
    private:
        GLuint textureID = 0;

    public: // variables
        LDDrift::ImageReader image_reader;
        std::pmr::vector<float> textureData;
        float colorMulti = 1.0f;

    public: // functions
        Texture();
        ~Texture();
        void SetColorMultiplierForTexture(float _colorMultiplier);
        [[nodiscard]] float GetColorMultiplierOfTexture() const;
        bool operator!=(const Texture& tex) const;
        bool operator==(const Texture& tex) const;
        void SetTextureCoordinates(const std::pmr::vector<float>& _textureCoordinates);
        [[nodiscard]] const std::pmr::vector<float>& GetTextureCoordinates() const;
        void GenerateTexture();
        void LoadTexture() const;
        void FreeTexture() const;
        [[nodiscard]] GLuint GetTextureID() const;
    };
}

#endif
