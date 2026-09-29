#ifndef LUCID_DRIFT_FILESYSTEMHND_H
#define LUCID_DRIFT_FILESYSTEMHND_H
#include <filesystem>
#include <fstream>
#include <string>
#include <cstring>
#include <ProjectWatchTower.h>
#include <Assertions.h>

namespace LDDrift
{
    /**
     * @class FileSystemHND
     * @brief A utility class for file system operations.
     *
     * Provides methods to create directories, files, and write data to files.
     * Handles file path settings and ensures file names are valid.
     *
     * @note This class is intended to simplify file handling tasks while ensuring
     *       that file names are valid and directories are created in a user-specific
     *       folder.
     */
    class FileSystemHND final
    {
    private:
        static std::filesystem::path home;
        static std::filesystem::path folderPath;

    private: // private functions
        static bool FileNameIsNotValid(const std::filesystem::path& path, const std::string& fileName);

    public:
        static void SetFolderPath(const std::filesystem::path& path, bool reset = false);
        static void CreateDirectory(const std::string& directoryName);
        static void CreateDirectoryWithInputPath(const std::filesystem::path& path);
        static void CreateFile(const std::string&);
        static void WriteToFile(const std::string& fileName, const char* data);
    };
}

#endif
