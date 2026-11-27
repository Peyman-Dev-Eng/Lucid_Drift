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
