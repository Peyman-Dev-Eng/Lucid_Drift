#include "FileSystemHND.h"

std::filesystem::path LDDrift::FileSystemHND::home;
std::filesystem::path LDDrift::FileSystemHND::folderPath;

void LDDrift::FileSystemHND::SetFolderPath(const std::filesystem::path& path, const bool reset) {
    if (reset || folderPath.empty()) {
        home = LDDrift::GetHostName();
        folderPath = home / path;
    } else {
        home = LDDrift::GetHostName();
        folderPath = folderPath / path;
    }
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
    const std::filesystem::path path = home / folderPath / directoryName;
    create_directories(path);
}

void LDDrift::FileSystemHND::CreateDirectoryWithInputPath(const std::filesystem::path& path) {
    create_directories(path);
}

void LDDrift::FileSystemHND::CreateFile(const std::string& fileName) {
    const std::filesystem::path path = folderPath / fileName;
    GLB_assert(!LDDrift::FileSystemHND::FileNameIsNotValid(folderPath, fileName))
    std::ofstream file(path);
}

void LDDrift::FileSystemHND::WriteToFile(const std::string& fileName, const char* data) {
    std::ofstream file((folderPath / fileName));
    COF_assert(file.is_open());
    file.write(data, static_cast<std::streamsize>(std::strlen(data)));
}
