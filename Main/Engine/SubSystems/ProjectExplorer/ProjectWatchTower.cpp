#include "ProjectWatchTower.h"

LDDrift::ProjectWatchTower::ProjectWatchTower() {
    projectPath = LDDrift::GetHostName();
}

void LDDrift::ProjectWatchTower::SetProjectPath(const std::filesystem::path& ProjectPath) {
    projectPath = LDDrift::GetHostName() / ProjectPath;
}

void LDDrift::ProjectWatchTower::CreateNewProject(const std::string& _projectName) {
    projectName = _projectName;
    projectPath = std::filesystem::path(LDDrift::GetHostName()) / _projectName;
    create_directories(projectPath);
}

std::string LDDrift::ProjectWatchTower::Extract::GetLastFileName(const std::string& _path) {
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

bool LDDrift::ProjectWatchTower::isFilePath(const std::filesystem::path& path) {
    bool isFile = true;
    for (const char& ch : path.string()) {
        if (ch == '/') {
            isFile = false;
            break;
        }
    }
    return isFile;
}

void LDDrift::ProjectWatchTower::SetPaths() {
    if (!paths.empty()) {
        paths.clear();
    }
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(projectPath)) {
        paths.push_back(entry.path());
    }
}

std::string LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(
    const std::string& fileName, std::vector<std::filesystem::path>& _paths) {
    for (std::filesystem::path& path : _paths) {
        if (std::string lastFileName = LDDrift::ProjectWatchTower::Extract::GetLastFileName(path.string());
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

std::string LDDrift::ProjectWatchTower::IsAvailableFileInProject(const std::string& fileName) const {
    std::string _is = NULL_VALUE;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(projectPath)) {
        std::string lastFileName =
            LDDrift::ProjectWatchTower::Extract::GetLastFileName(entry.path().string());
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

const std::filesystem::path& LDDrift::ProjectWatchTower::GetProjectPath() const {
    return projectPath;
}

std::string LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(
    const std::filesystem::path& filePath) {
    long int counter = static_cast<long int>(filePath.string().size() - 1);
    while (counter > LOWER_BOUND_WHILE_LOOP && filePath.string()[counter] != '/') {
        --counter;
    }
    return filePath.string().substr(0, counter);
}

void LDDrift::ProjectWatchTower::WriteCodeToFile(const std::filesystem::path& fileName, const char* text) const {
    NPV_assert(text != nullptr);
    if (isFilePath(fileName)) {
        std::ofstream out(projectPath / fileName.string());
        out.write(text, static_cast<std::streamsize>(strlen(text)));
        return;
    } else {
        create_directories(projectPath / LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(fileName));
        std::ofstream out(projectPath / fileName.string());
        out.write(text, static_cast<std::streamsize>(strlen(text)));
        return;
    }
}

std::vector<std::string> LDDrift::ProjectWatchTower::GetProjectDetails() const {
    std::vector<std::string> projectDetails;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(projectPath)) {
        projectDetails.push_back(entry.path().string());
    }
    return projectDetails;
}

const std::string& LDDrift::ProjectWatchTower::GetProjectName() const {
    return projectName;
}

LDDrift::ProjectWatchTower::~ProjectWatchTower() = default;
