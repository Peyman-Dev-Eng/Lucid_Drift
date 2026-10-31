#ifndef LUCID_DRIFT_IMAGEREADER_H
#define LUCID_DRIFT_IMAGEREADER_H
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <filesystem>

namespace LDDrift
{
    class ImageReader final
    {
    private:
        struct Image
        {
            unsigned char* pixels = nullptr;
            int width = 0, height = 0;
            int channels = 0;
            const int desiredChannels = 4;
        };
        Image image;
    public:
        ImageReader();
        explicit ImageReader(const std::filesystem::path& imagePath);
        [[nodiscard]] const Image& GetImage() const;
        ~ImageReader();
    };
}

#endif
