#include "ProjectWatchTower.h"

#include <GLFW/glfw3.h>

LDDrift::Explorer::ProjectWatchTower::ProjectWatchTower() {
    projectPath = LDDrift::GetHostName();
}

void LDDrift::Explorer::ProjectWatchTower::SetProjectPath(const std::filesystem::path& ProjectPath) {
    projectPath = LDDrift::GetHostName() / ProjectPath;
}

void LDDrift::Explorer::ProjectWatchTower::CreateNewProject(const std::string& _projectName) {
    projectName = _projectName;
    LDDrift::FileSystemHND::CreateDirectory(_projectName);
}

std::string LDDrift::Explorer::ProjectWatchTower::Extract::GetLastFileName(const std::string& _path) const {
    const std::size_t _pathLength = _path.size();
    std::string result;
    std::size_t counter = 0;
    while (counter < UPPER_BOUND_WHILE_LOOP && _path[_pathLength - 1 - counter] != '/') {
        result += _path[counter];
        ++counter;
    }
    if (counter >= UPPER_BOUND_WHILE_LOOP) {
        std::cerr << RED << "Error: Failed to extract the last file name because the maximum search limit was exceeded."
            << RESET << std::endl;
        return NULL_VALUE;
    }
    return result;
}

void LDDrift::Explorer::ProjectWatchTower::SetPaths() {
    if (!paths.empty()) {
        paths.clear();
    }
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(projectPath)) {
        paths.push_back(entry.path());
    }
}

std::string LDDrift::Explorer::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(
    const std::string& fileName, std::vector<std::filesystem::path>& _paths) const {
    for (std::filesystem::path& path : _paths) {
        if (std::string lastFileName = LDDrift::Explorer::ProjectWatchTower::Extract::GetLastFileName(path.string());
            lastFileName == NULL_VALUE || lastFileName != fileName) {
            continue;
        }
        std::size_t counter = path.string().size() - 1;
        while (counter < UPPER_BOUND_WHILE_LOOP && path.string()[counter] != '/') {
            --counter;
        }
        OOR_assert(counter > 0)
        return path.string().substr(0, counter);
    }
    return NULL_VALUE;
}

std::string LDDrift::Explorer::ProjectWatchTower::IsAvailableFileInProject(const std::string& fileName) const {
    std::string _is = NULL_VALUE;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(projectPath)) {
        std::string lastFileName =
            extractor.GetLastFileName(entry.path().string());
        if (lastFileName == NULL_VALUE) {
            continue;
        }
        if (fileName == lastFileName) {
            _is = entry.path().string();
            break;
        }
    }
    return _is;
}

const std::filesystem::path& LDDrift::Explorer::ProjectWatchTower::GetProjectPath() const {
    return projectPath;
}

std::string LDDrift::Explorer::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(
    const std::filesystem::path& filePath) {
    long int counter = static_cast<long int>(filePath.string().size() - 1);
    while (counter > LOWER_BOUND_WHILE_LOOP && filePath.string()[counter] != '/') {
        --counter;
    }
    return filePath.string().substr(0, counter);
}

void LDDrift::Explorer::ProjectWatchTower::WriteCodeToFile(const std::string& fileName, const char* text) const {
    NPV_assert(text != nullptr);
    if (const std::string filePath = LDDrift::Explorer::ProjectWatchTower::IsAvailableFileInProject(fileName);
        filePath != NULL_VALUE) {
        LDDrift::FileSystemHND::SetFolderPath(extractor.GetLastFileName(std::filesystem::path(filePath)));
        LDDrift::FileSystemHND::WriteToFile(fileName, text);
    } else {
        std::string BWLFN = LDDrift::Explorer::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(fileName);
        LDDrift::FileSystemHND::CreateDirectoryWithInputPath(projectPath / BWLFN);
        LDDrift::FileSystemHND::SetFolderPath(projectPath, true);
        const std::string lastFileName = extractor.GetLastFileName(fileName);
        LDDrift::FileSystemHND::CreateFile(lastFileName);
        LDDrift::FileSystemHND::WriteToFile(fileName, text);
    }
}

std::vector<std::string> LDDrift::Explorer::ProjectWatchTower::GetProjectDetails() const {
    std::vector<std::string> projectDetails;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(projectPath)) {
        projectDetails.push_back(entry.path().string());
    }
    return projectDetails;
}

const std::string& LDDrift::Explorer::ProjectWatchTower::GetProjectName() const {
    return projectName;
}

LDDrift::Explorer::ProjectWatchTower::~ProjectWatchTower() = default;
