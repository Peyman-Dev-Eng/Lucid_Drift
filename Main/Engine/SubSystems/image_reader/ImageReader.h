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
    public:
        ImageReader();
        explicit ImageReader(const std::filesystem::path& imagePath);
        void LoadImage(const std::filesystem::path& imagePath);
        [[nodiscard]] const Image& GetImage() const;
        ~ImageReader();
    };
}

#endif
