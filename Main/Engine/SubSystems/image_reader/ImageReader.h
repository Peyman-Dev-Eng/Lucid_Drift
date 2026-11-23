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
