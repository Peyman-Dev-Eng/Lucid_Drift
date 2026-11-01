#include "Texture.h"

LDDrift::Texture::Texture() = default;

LDDrift::Texture::~Texture() {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

bool LDDrift::Texture::operator!=(const Texture& tex) const {
    return !(*this == tex);
}

bool LDDrift::Texture::operator==(const Texture& tex) const {
    if (this == &tex) {
        return true;
    }
    return this->textureID == tex.textureID && image_reader.GetImage().pixels == tex.image_reader.GetImage().pixels;
}

GLuint LDDrift::Texture::GetTextureID() const {
    return textureID;
}

void LDDrift::Texture::GenerateTexture() {
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
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void LDDrift::Texture::LoadTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void LDDrift::Texture::FreeTexture() const {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

void LDDrift::Texture::SetTextureCoordinates(const std::vector<float>& _textureCoordinates) {
    textureData = _textureCoordinates;
}

const std::vector<float>& LDDrift::Texture::GetTextureCoordinates() const {
    return textureData;
}
