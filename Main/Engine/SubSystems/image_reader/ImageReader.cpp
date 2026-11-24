// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#define STB_IMAGE_IMPLEMENTATION
#include "ImageReader.h"

LDDrift::ImageReader::ImageReader() = default;

LDDrift::ImageReader::ImageReader(const std::filesystem::path& imagePath, const int& _desiredChannels) {
    image.pixels = stbi_load(imagePath.c_str(), &image.width, &image.height,
                             &image.channels, _desiredChannels);
    if (!image.pixels) {
        throw std::runtime_error(stbi_failure_reason());
    }
    CanFree = true;
}

void LDDrift::ImageReader::LoadImage(const std::filesystem::path& imagePath, const int& _desiredChannels) {
    image.pixels = stbi_load(imagePath.c_str(), &image.width, &image.height,
                             &image.channels, _desiredChannels);
    if (!image.pixels) {
        throw std::runtime_error(stbi_failure_reason());
    }
    CanFree = true;
}

const LDDrift::ImageReader::Image& LDDrift::ImageReader::GetImage() const { return image; }

void LDDrift::ImageReader::FreeImage() {
    if (CanFree) {
        stbi_image_free(image.pixels);
        CanFree = false;
    }
}

LDDrift::ImageReader::~ImageReader() {
    if (CanFree) {
        stbi_image_free(image.pixels);
        CanFree = false;
    }
}
