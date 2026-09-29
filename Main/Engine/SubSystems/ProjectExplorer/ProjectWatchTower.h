#ifndef LUCID_DRIFT_PROJECTEXPLORER_H
#define LUCID_DRIFT_PROJECTEXPLORER_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <FileSystemHND.h>
#include <Assertions.h>
#include <cstdlib>
#include <vector>
#define NULL_VALUE "NULL_VALUE"
#define LOWER_BOUND_WHILE_LOOP (-1)
#define UPPER_BOUND_WHILE_LOOP 100

namespace LDDrift
{
    constexpr std::string GetHostName() {
        std::string homeSystemName;
#ifdef _WIN32
        homeSystemName = std::getenv("COMPUTERNAME");
#elifdef __linux__
        homeSystemName = std::getenv("HOME");
#else
        homeSystemName = "";
#endif
        return homeSystemName;
    }

    namespace Explorer
    {
        // This struct is for storing the folders and files of the game project you are building using this engine.
        class ProjectWatchTower
        {
        private:
            std::filesystem::path projectPath;
            std::string projectName;
            std::vector<std::filesystem::path> paths;

        private:
            class Extract
            {
            public:
                [[nodiscard]] std::string GetLastFileName(const std::string& _path) const;
                [[nodiscard]] std::string GetBodyWithoutLastFileName(const std::string& fileName, std::vector<std::filesystem::path>& _paths) const;
                [[nodiscard]] static std::string GetBodyWithoutLastFileName(const std::filesystem::path& filePath);
            };
        private:
            Extract extractor;

        public:
            ProjectWatchTower();
            void SetPaths();
            [[nodiscard]] std::string IsAvailableFileInProject(const std::string& fileName) const;
            void CreateNewProject(const std::string& _projectName);
            void SetProjectPath(const std::filesystem::path& ProjectPath);
            void WriteCodeToFile(const std::string& fileName, const char* text) const;
            [[nodiscard]] const std::filesystem::path& GetProjectPath() const;
            [[nodiscard]] std::vector<std::string> GetProjectDetails() const;
            [[nodiscard]] const std::string& GetProjectName() const;
            ~ProjectWatchTower();
        };
    }
}

#endif
