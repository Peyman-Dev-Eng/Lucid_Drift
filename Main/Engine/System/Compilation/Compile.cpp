#include "Compile.h"

LDDrift::Compile::Compile() = default;

void LDDrift::Compile::initialize() {}

void LDDrift::Compile::SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTower_Pointer) {
    ProjectWatchTowerPTR = projectWatchTower_Pointer;
}

void LDDrift::Compile::SetCompilePath(std::string& compileMess) const {
    const std::vector<std::filesystem::path>& filePaths = ProjectWatchTowerPTR->GetPaths();
    compileMess = "g++ -shared -fPIC ";
    for (const std::filesystem::path& filePath : filePaths) {
        if (std::filesystem::is_directory(filePath) ||
            LDDrift::ProjectWatchTower::isCmakeFile(filePath) ||
            !(LDDrift::ProjectWatchTower::PathIsFile(filePath))) {
            continue;
        } else {
            std::cout << filePath.string() << std::endl;
            compileMess += filePath.string();
        }
    }
    compileMess += " ";
#ifdef __linux__
    compileMess += "-o " + (ProjectWatchTowerPTR->GetProjectPath() / "BUILD").string() + "/" +
        ProjectWatchTowerPTR->GetProjectName() + ".so";
#elifdef _WIN32
    compileMess += "-o " + (ProjectWatchTowerPTR->GetProjectPath() / "BUILD").string() + "/" +
        ProjectWatchTowerPTR->GetProjectName() + ".dll";
#endif
    std::cout << compileMess << std::endl;
}

void LDDrift::Compile::compile() {
    std::string compileMess;
    this->SetCompilePath(compileMess);
    std::system(compileMess.c_str());
}

LDDrift::Compile::~Compile() = default;
