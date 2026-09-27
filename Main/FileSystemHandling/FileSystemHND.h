#ifndef LUCID_DRIFT_FILESYSTEMHND_H
#define LUCID_DRIFT_FILESYSTEMHND_H
#include <filesystem>
#include <fstream>
#include <string>
#include <cstring>
#include <Assertions.h>

namespace LDDrift
{
    class FileSystemHND final
    {
    private:
        std::filesystem::path home;
        std::filesystem::path folderPath;

    private: // private functions
        static bool FileNameIsNotValid(const std::filesystem::path& path, const std::string& fileName);

    public:
        FileSystemHND();
        void CreateDirectory(const std::string& directoryName);
        void CreateFile(const std::string&) const;
        void WriteToFile(const std::string& fileName, const char* data) const;
        ~FileSystemHND();
    };
}

#endif
