#include "Texture.h"

LDDrift::Texture::Texture() = default;

LDDrift::Texture::~Texture() {
    glDeleteTextures(1, &textureID);
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

void LDDrift::Texture::LoadTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
