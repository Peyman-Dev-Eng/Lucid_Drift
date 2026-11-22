#define STB_IMAGE_IMPLEMENTATION
#include "ImageReader.h"

LDDrift::ImageReader::ImageReader() = default;

LDDrift::ImageReader::ImageReader(const std::filesystem::path& imagePath, const int& _desiredChannels) {
    image.pixels = stbi_load(imagePath.c_str(), &image.width, &image.height,
                             &image.channels, 0);
    if (!image.pixels) {
        throw std::runtime_error(stbi_failure_reason());
    }
    CanFree = true;
}

void LDDrift::ImageReader::LoadImage(const std::filesystem::path& imagePath, const int& _desiredChannels) {
    image.pixels = stbi_load(imagePath.c_str(), &image.width, &image.height,
                             &image.channels, 0);
    if (!image.pixels) {
        throw std::runtime_error(stbi_failure_reason());
    }
    CanFree = true;
}

const LDDrift::ImageReader::Image& LDDrift::ImageReader::GetImage() const { return image; }

void LDDrift::ImageReader::FreeImage() const {
    if (CanFree) {
        stbi_image_free(image.pixels);
    }
}

LDDrift::ImageReader::~ImageReader() {
    if (CanFree) {
        stbi_image_free(image.pixels);
    }
}
