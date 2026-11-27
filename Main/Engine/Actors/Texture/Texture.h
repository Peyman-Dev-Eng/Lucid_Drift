// Copyright (C) 2026 Peyman
//
// This file is part of Lucid Drift.
// Lucid Drift is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// This software is distributed without any warranty.
// See the LICENSE file for the full license text.
// See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.

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
