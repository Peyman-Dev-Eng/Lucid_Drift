#include "ProjectWatchTower.h"

#include <chrono>

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
    std::filesystem::path engineRoot =
        LDDrift::func::GetExecutablePath();
    engineRoot = engineRoot.parent_path().parent_path();
    // Verify that engineRoot points to the engine source directory.
    if (!std::filesystem::exists(engineRoot / "CMakeLists.txt")) {
        std::cerr
            << "Error: Lucid_Drift CMakeLists.txt was not found at: "
            << engineRoot << '\n';
        return;
    }

    const auto apiInclude =
        engineRoot / "Main" / "Engine" / "API";

    const auto projectExplorerInclude =
        engineRoot / "Main" / "SubSystems" / "ProjectExplorer";

    const auto functionsInclude =
        engineRoot / "Main" / "Engine" / "Functions";

    const auto outputDirectory = this->projectPath / "BUILD";

    std::filesystem::create_directories(outputDirectory);

    // generic_string() produces forward slashes on Windows and Linux.
    std::ostringstream cmakeTemplate;

    cmakeTemplate
        << "cmake_minimum_required(VERSION 4.3)\n\n"

        << "project(\"" << projectName
        << "\" LANGUAGES CXX C)\n\n"

        << "set(CMAKE_CXX_STANDARD 26)\n"
        << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
        << "set(CMAKE_CXX_EXTENSIONS OFF)\n\n"

        << "set(LUCID_DRIFT_ROOT \""
        << engineRoot.generic_string() << "\")\n\n"

        << "set(USER_SCRIPT_OUTPUT_DIR "
        << "\"${CMAKE_CURRENT_SOURCE_DIR}/BUILD\")\n\n"

        // Make the Engine target available to the user project.
        << "add_subdirectory("
        << "\"${LUCID_DRIFT_ROOT}\" "
        << "\"${CMAKE_BINARY_DIR}/LucidDriftEngine\")\n\n"

        // Build a shared library instead of an executable.
        << "add_library(LucidDriftUserScript SHARED\n"
        << "    main.cpp\n"
        << ")\n\n"

        << "target_link_libraries(LucidDriftUserScript PRIVATE Engine)\n\n"

        << "target_include_directories(LucidDriftUserScript PRIVATE\n"
        << "    \"" << apiInclude.generic_string() << "\"\n"
        << "    \"" << projectExplorerInclude.generic_string() << "\"\n"
        << "    \"" << functionsInclude.generic_string() << "\"\n"
        << ")\n\n"

        << "set_target_properties(LucidDriftUserScript PROPERTIES\n"
        << "    PREFIX \"\"\n"
        << "    OUTPUT_NAME \"${PROJECT_NAME}\"\n"
        << "    LIBRARY_OUTPUT_DIRECTORY "
        << "\"${USER_SCRIPT_OUTPUT_DIR}\"\n"
        << "    RUNTIME_OUTPUT_DIRECTORY "
        << "\"${USER_SCRIPT_OUTPUT_DIR}\"\n"
        << "    BUILD_RPATH \"$ORIGIN\"\n"
        << ")\n\n"

        // Keep Debug and Release outputs in BUILD, including
        // when using a multi-configuration generator.
        << "foreach(CONFIG IN ITEMS "
        << "DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)\n"
        << "    set_target_properties(LucidDriftUserScript PROPERTIES\n"
        << "        \"LIBRARY_OUTPUT_DIRECTORY_${CONFIG}\" "
        << "\"${USER_SCRIPT_OUTPUT_DIR}\"\n"
        << "        \"RUNTIME_OUTPUT_DIRECTORY_${CONFIG}\" "
        << "\"${USER_SCRIPT_OUTPUT_DIR}\"\n"
        << "    )\n"
        << "endforeach()\n\n"

        // Copy the shared engine library beside the user library.
        << "add_custom_command(TARGET LucidDriftUserScript POST_BUILD\n"
        << "    COMMAND ${CMAKE_COMMAND} -E copy_if_different\n"
        << "        \"$<TARGET_FILE:Engine>\"\n"
        << "        \"$<TARGET_FILE_DIR:LucidDriftUserScript>\"\n"
        << "    VERBATIM\n"
        << ")\n";

    std::ofstream outFile(this->projectPath / "CMakeLists.txt");

    if (!outFile.is_open()) {
        std::cerr
            << "Error: Failed to create the CMakeLists.txt file.\n";
        return;
    }

    outFile << cmakeTemplate.str();

    if (!outFile) {
        std::cerr
            << "Error: Failed to write the CMakeLists.txt file.\n";
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
}

LDDrift::ProjectWatchTower::~ProjectWatchTower() = default;
