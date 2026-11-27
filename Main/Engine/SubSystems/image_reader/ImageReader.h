/*
* Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */
#ifndef LUCID_DRIFT_IMAGE_READER_H
#define LUCID_DRIFT_IMAGE_READER_H
#include <stb_image.h>
#include <filesystem>

namespace LDDrift
{
    class ImageReader final
    {
    public:
        struct Image
        {
            unsigned char* pixels = nullptr;
            int width = 0, height = 0;
            int channels = 0;
            const int desiredChannels = 3;
        };
    private:
        Image image;
        bool CanFree = false;
    public:
        ImageReader();
        explicit ImageReader(const std::filesystem::path& imagePath, const int& _desiredChannels = 0);
        void LoadImage(const std::filesystem::path& imagePath, const int& _desiredChannels = 0);
        [[nodiscard]] const Image& GetImage() const;
        void FreeImage();
        ~ImageReader();
    };
}

#endif
