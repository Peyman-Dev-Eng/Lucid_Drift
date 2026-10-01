#ifndef LUCID_DRIFT_PROJECTEXPLORER_H
#define LUCID_DRIFT_PROJECTEXPLORER_H
#include <filesystem>
#include <fstream>
#include <functions.h>
#include <iostream>
#define FMT_USE_CONSTEVAL 0
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <string>
#include <unordered_map>
#include <cstring>
#include <Assertions.h>
#include <cstdlib>
#include <vector>
#define NULL_STR_VALUE "NULL_VALUE"
#define LOWER_BOUND_WHILE_LOOP (-1)
#define UPPER_BOUND_WHILE_LOOP 100

namespace LDDrift
{

    // This struct is for storing the folders and files of the game project you are building using this engine.
    class ProjectWatchTower
    {
    private:
        std::filesystem::path projectPath;
        std::string projectName;
        std::vector<std::filesystem::path> paths;

    public:
        class Extract
        {
        public:
            static std::string GetLastFileName(const std::string& _path);
            static std::string GetBodyWithoutLastFileName(const std::string& fileName,
                                                          std::vector<std::filesystem::path>& _paths);
            static std::string GetBodyWithoutLastFileName(const std::filesystem::path& filePath);
        };
        static bool isFilePath(const std::filesystem::path& path);

    public:
        ProjectWatchTower();
        void SetPaths();
        [[nodiscard]] const std::vector<std::filesystem::path>& GetPaths();
        [[nodiscard]] std::string IsAvailableFileInProject(const std::string& fileName) const;
        void CreateCmakeListTXT_File() const;
        void CreateNewProject(const std::string& _projectName);
        void SetProjectPath(const std::filesystem::path& ProjectPath);
        void WriteCodeToFile(const std::filesystem::path& fileName, const char* text) const;
        [[nodiscard]] const std::filesystem::path& GetProjectPath() const;
        [[nodiscard]] std::vector<std::string> GetProjectDetails() const;
        [[nodiscard]] const std::string& GetProjectName() const;
        ~ProjectWatchTower();
    };
}

#endif
