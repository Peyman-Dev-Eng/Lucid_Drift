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
#ifndef LUCID_DRIFT_PROJECT_EXPLORER_H
#define LUCID_DRIFT_PROJECT_EXPLORER_H
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
#include <thread>
#include <vector>
#define NULL_STRING "NULL_VALUE"
#define LOWER_BOUND_WHILE_LOOP (-1)
#define UPPER_BOUND_WHILE_LOOP 100

namespace LDDrift
{

    // This struct is for storing the folders and files of the game project you are building using this engine.
    class ProjectWatchTower final
    {
    private:
        std::filesystem::path projectPath;
        std::string projectName;
        std::pmr::vector<std::filesystem::path> paths;
        std::filesystem::path buildFolderPath;
        std::string objectFileName;
        std::filesystem::path compileLogFilePath;

    public:
        class Extract
        {
        public:
            static std::string GetLastFileName(const std::string& _path);
            static std::string GetBodyWithoutLastFileName(const std::string& fileName,
                                                          std::pmr::vector<std::filesystem::path>& _paths);
            static std::string GetBodyWithoutLastFileName(const std::filesystem::path& filePath);
            static std::pmr::vector<std::string> ExtractPaths(const std::filesystem::path& path);
        };
        static bool isFilePath(const std::filesystem::path& path);

    public:
        ProjectWatchTower();
        void SetPaths();
        static bool PathIsFile(const std::filesystem::path& path) ;
        [[nodiscard]] const std::pmr::vector<std::filesystem::path>& GetPaths();
        [[nodiscard]] std::string IsAvailableFileInProject(const std::string& fileName) const;
        void CreateBuildFolder();
        void CreateCmakeListsTxtFile() const;
        void CreateCompileLogFile();
        [[nodiscard]] bool FindFile(const std::string& fileName) const;
        static bool isCmakeFile(const std::filesystem::path& path) ;
        void CreateNewProject(const std::string& _projectName);
        void SetProjectPath(const std::filesystem::path& ProjectPath);
        void WriteCodeToFile(const std::filesystem::path& fileName, const char* text) const;
        void CreateNewFile(const std::filesystem::path& fileName) const;
        void RemoveBuildFile() const;
        void RemoveFile(const std::string& fileName);
        [[nodiscard]] const std::filesystem::path& GetBuildFolderPath() const;
        [[nodiscard]] const std::filesystem::path& GetProjectPath() const;
        [[nodiscard]] std::pmr::vector<std::string> GetProjectDetails() const;
        [[nodiscard]] const std::filesystem::path& GetCompileLogPath() const;
        [[nodiscard]] const std::string& GetProjectName() const;
        ~ProjectWatchTower();
    };
}

#endif
