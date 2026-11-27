// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#include "Texture.h"

LDDrift::Actors::Texture::Texture() = default;

LDDrift::Actors::Texture::~Texture() {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

bool LDDrift::Actors::Texture::operator!=(const Texture& tex) const {
    return !(*this == tex);
}

bool LDDrift::Actors::Texture::operator==(const Texture& tex) const {
    if (this == &tex) {
        return true;
    }
    return this->textureID == tex.textureID && image_reader.GetImage().pixels == tex.image_reader.GetImage().pixels;
}

GLuint LDDrift::Actors::Texture::GetTextureID() const {
    return textureID;
}

void LDDrift::Actors::Texture::GenerateTexture() {
    const auto image = image_reader.GetImage();
    // generate texture on v_ram
    glGenTextures(1, &textureID);
    // bind texture 2d on v_ram
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (image.channels == 1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, image.width, image.height,
                     0, GL_RED, GL_UNSIGNED_BYTE, image.pixels);
    } else if (image.channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image.width, image.height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
    } else if (image.channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);
    } else {
        throw std::runtime_error("Unsupported image channels");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void LDDrift::Actors::Texture::LoadTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void LDDrift::Actors::Texture::FreeTexture() const {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

void LDDrift::Actors::Texture::SetTextureCoordinates(const std::pmr::vector<float>& _textureCoordinates) {
    textureData = _textureCoordinates;
}

const std::pmr::vector<float>& LDDrift::Actors::Texture::GetTextureCoordinates() const {
    return textureData;
}

void LDDrift::Actors::Texture::SetColorMultiplierForTexture(const float _colorMultiplier) {
    colorMulti = _colorMultiplier;
}

float LDDrift::Actors::Texture::GetColorMultiplierOfTexture() const {
    return colorMulti;
}
