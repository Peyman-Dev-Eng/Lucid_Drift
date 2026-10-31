#include "ImageReader.h"

LDDrift::ImageReader::ImageReader() = default;

LDDrift::ImageReader::ImageReader(const std::filesystem::path& imagePath) {
    image.pixels = stbi_load(imagePath.c_str(), &image.width, &image.height,
                             &image.channels, image.desiredChannels);
    if (!image.pixels) {
        throw std::runtime_error(stbi_failure_reason());
    }
}

const LDDrift::ImageReader::Image& LDDrift::ImageReader::GetImage() const { return image; }

LDDrift::ImageReader::~ImageReader() {
    stbi_image_free(image.pixels);
}
