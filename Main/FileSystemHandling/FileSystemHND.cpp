#include "FileSystemHND.h"


LDDrift::FileSystemHND::FileSystemHND() {
#ifdef __linux__
    home = std::filesystem::path(std::getenv("HOME"));
#elifdef _WIN32
    home = std::filesystem::path(std::getenv("USERPROFILE"));
#endif
}

bool LDDrift::FileSystemHND::FileNameIsNotValid(const std::filesystem::path& path,
                                                const std::string& fileName) {
    bool fileNameIsNotValid = false;
    for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator(path)) {
        if (file.path().filename() == fileName) {
            fileNameIsNotValid = true;
            break;
        }
    }
    return fileNameIsNotValid;
}

void LDDrift::FileSystemHND::CreateDirectory(const std::string& directoryName) {
#ifdef __linux__
    const std::filesystem::path path = home / directoryName;
    std::filesystem::create_directories(path);
    folderPath = path;
#elifdef _WIN32
    std::filesystem::path path = home / "Desktop" / directoryName;
    std::filesystem::create_directories(path);
    folderPath = path;
#endif
}

void LDDrift::FileSystemHND::CreateFile(const std::string& fileName) const {
    const std::filesystem::path path = folderPath / fileName;
    GLB_assert(!LDDrift::FileSystemHND::FileNameIsNotValid(folderPath, fileName))
    std::ofstream file(path);
}

void LDDrift::FileSystemHND::WriteToFile(const std::string& fileName, const char* data) const {
    std::ofstream file((folderPath / fileName));
    COF_assert(file.is_open());
    file.write(data, static_cast<std::streamsize>(std::strlen(data)));
}

LDDrift::FileSystemHND::~FileSystemHND() = default;
