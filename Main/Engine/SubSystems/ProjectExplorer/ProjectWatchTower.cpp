#include "ProjectWatchTower.h"

LDDrift::ProjectWatchTower::ProjectWatchTower() {
    projectPath = LDDrift::func::GetHostName();
}

void LDDrift::ProjectWatchTower::SetProjectPath(const std::filesystem::path& ProjectPath) {
    projectPath = LDDrift::func::GetHostName() / ProjectPath;
}

void LDDrift::ProjectWatchTower::CreateNewProject(const std::string& _projectName) {
    projectName = _projectName;
    projectPath = std::filesystem::path(LDDrift::func::GetHostName()) / _projectName;
    create_directories(projectPath);
    this->CreateBuildFolder();
    this->CreateCmakeListsTxtFile();
}

bool LDDrift::ProjectWatchTower::isCmakeFile(const std::filesystem::path& path) {
    const std::string stringPath = path.string();
    if (const std::size_t pathLen = stringPath.size();
        stringPath[pathLen - 1] == 't' &&
        stringPath[pathLen - 2] == 'x' &&
        stringPath[pathLen - 3] == 't' &&
        stringPath[pathLen - 4] == '.') {
        return true;
    }
    return false;
}

void LDDrift::ProjectWatchTower::CreateCmakeListsTxtFile() const {
    std::filesystem::path executablePath = LDDrift::func::GetExecutablePath();
    executablePath = (executablePath.parent_path().parent_path()) / "Main";
    std::string initMainFile = "int main() {\n\treturn 0;\n}";
    std::ofstream mainFile((projectPath / "main.cpp").string());
    mainFile << initMainFile;
    std::string cmakeTemplate = R"(cmake_minimum_required(VERSION 4.3)
project({} CXX C)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(")" + executablePath.string() + R"(" "${CMAKE_BINARY_DIR}/LucidDriftEngine")

add_executable({} main.cpp)

target_link_libraries({} PUBLIC Engine)
)";
    size_t pos = 0;
    while ((pos = cmakeTemplate.find("{}", pos)) != std::string::npos) {
        cmakeTemplate.replace(pos, 2, projectName);
        pos += projectName.length();
    }

    if (std::ofstream outFile(this->projectPath / "CMakeLists.txt"); outFile.is_open()) {
        outFile << cmakeTemplate;
        outFile.close();
    } else {
        std::cerr << "Error: Failed to create the CMakeLists.txt file." << std::endl;
        return;
    }
}

const std::filesystem::path& LDDrift::ProjectWatchTower::GetBuildFolderPath() const {
    return buildFolderPath;
}

std::vector<std::string> LDDrift::ProjectWatchTower::Extract::ExtractPaths(const std::filesystem::path& path) {
    std::vector<std::string> result;
    const std::string pathString = path.string();
    std::size_t lastPos = path.string().size() - 1;
    std::size_t currentPos = lastPos - 1;
    while (currentPos > 0) {
        while (pathString[currentPos] != '/') {
            --currentPos;
        }
        result.push_back(pathString.substr(currentPos + 1, lastPos - currentPos));
        lastPos = currentPos - 1;
        currentPos = lastPos - 1;
    }
    return result;
}

std::string LDDrift::ProjectWatchTower::Extract::GetLastFileName(const std::string& _path) {
    const int _pathLength = static_cast<int>(_path.size());
    std::string result;
    int counter = _pathLength - 1;
    while (counter >= LOWER_BOUND_WHILE_LOOP && _path[counter] != '/') {
        result += _path[counter];
        --counter;
    }
    if (counter < LOWER_BOUND_WHILE_LOOP) {
        std::cerr << RED << "Error: Failed to extract the last file name because the maximum search limit was exceeded."
            << RESET << std::endl;
        return NULL_STR_VALUE;
    }
    std::ranges::reverse(result);
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

const std::vector<std::filesystem::path>& LDDrift::ProjectWatchTower::GetPaths() {
    return paths;
}

void LDDrift::ProjectWatchTower::SetPaths() {
    if (!paths.empty()) {
        paths.clear();
    }
    std::filesystem::recursive_directory_iterator iterator(projectPath);
    for (const std::filesystem::directory_entry& entry : iterator) {
        if (entry.path().filename() == "cmake-build-debug" || entry.path().filename() == ".idea" || entry.path().filename() == "BUILD") {
            if (entry.is_directory()) {
                iterator.disable_recursion_pending();
            }
            continue;
        }
        paths.push_back(entry.path());
    }
}

std::string LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(
    const std::string& fileName, std::vector<std::filesystem::path>& _paths) {
    for (std::filesystem::path& path : _paths) {
        if (std::string lastFileName = LDDrift::ProjectWatchTower::Extract::GetLastFileName(path.string());
            lastFileName == NULL_STR_VALUE || lastFileName != fileName) {
            continue;
        }
        std::size_t counter = path.string().size() - 1;
        while (counter < UPPER_BOUND_WHILE_LOOP && path.string()[counter] != '/') {
            --counter;
        }
        OOR_assert(counter > 0)
        return path.string().substr(0, counter);
    }
    return NULL_STR_VALUE;
}

bool LDDrift::ProjectWatchTower::PathIsFile(const std::filesystem::path& path) {
    const std::size_t _pathLength = path.string().size() - 1;
    if (const std::string pathString = path.string();
        pathString[_pathLength] == 'h' && pathString[_pathLength - 1] == '.') {
        return true;
    } else if (pathString[_pathLength] == 'p' &&
        pathString[_pathLength - 1] == 'p' &&
        pathString[_pathLength - 2] == 'c' &&
        pathString[_pathLength - 3] == '.') {
        return true;
    }
    return false;
}

std::string LDDrift::ProjectWatchTower::IsAvailableFileInProject(const std::string& fileName) const {
    std::string _is = NULL_STR_VALUE;
    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(projectPath)) {
        std::string lastFileName =
            LDDrift::ProjectWatchTower::Extract::GetLastFileName(entry.path().string());
        if (lastFileName == NULL_STR_VALUE) {
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
        std::cout << "Successfully written project: " << projectPath / fileName.string() << std::endl;
        return;
    } else {
        create_directories(projectPath / LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(fileName));
        std::ofstream out(projectPath / fileName.string());
        out.write(text, static_cast<std::streamsize>(strlen(text)));
        std::cout << "Successfully written project: " << projectPath / fileName.string() << std::endl;
        return;
    }
}

void LDDrift::ProjectWatchTower::CreateNewFile(const std::filesystem::path& fileName) const {
    if (isFilePath(fileName)) {
        std::ofstream out(projectPath / fileName.string());
        std::cout << "File created successfully. You can now use the file. PATH: " << projectPath / fileName.string() <<
            std::endl;
        return;
    } else {
        create_directories(projectPath / LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName(fileName));
        std::ofstream out(projectPath / fileName.string());
        std::cout << "File created successfully. You can now use the file. PATH: " << projectPath / fileName.string() <<
            std::endl;
        return;
    }
}

bool LDDrift::ProjectWatchTower::FindFile(const std::string& fileName) const {
    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(projectPath)) {
        if (Extract::GetLastFileName(entry.path().string()) == fileName) {
            return true;
        }
    }
    return false;
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

void LDDrift::ProjectWatchTower::CreateBuildFolder() {
    buildFolderPath = projectPath / "BUILD";
    create_directories(buildFolderPath);
    std::string runCommand = "cmake -S ";
    runCommand += projectPath.string();
    runCommand += " -B ";
    runCommand += buildFolderPath.string();
    runCommand += " -G Ninja";
    std::thread createBuildFolderThread([runCommand]()
    {
        std::system(runCommand.c_str());
    });
    if (createBuildFolderThread.joinable()) {
        createBuildFolderThread.join();
    }
}

LDDrift::ProjectWatchTower::~ProjectWatchTower() = default;
