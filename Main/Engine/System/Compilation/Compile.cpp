#include "Compile.h"

LDDrift::Compile::Compile() = default;

void LDDrift::Compile::initialize() {}

void LDDrift::Compile::SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTower_Pointer) {
    ProjectWatchTowerPTR = projectWatchTower_Pointer;
}

void LDDrift::Compile::SetCompilePath(std::string& compileMess) {
    const std::vector<std::filesystem::path>& filePaths = ProjectWatchTowerPTR->GetPaths();
    compileMess = "g++ -shared -fPIC ";
    for (const std::filesystem::path& filePath : filePaths) {
        if (LDDrift::ProjectWatchTower::PathIsFile(filePath)) {
            compileMess += (filePath.string() + " ");
        }
    }
#ifdef __linux__
    compileMess += "-o " + ProjectWatchTowerPTR->GetProjectName() + ".so";
#elifdef _WIN32
    compileMess += "-o " + ProjectWatchTowerPTR->GetProjectName() + ".dll";
#endif
}

void LDDrift::Compile::compile() {
    std::string compileMess;
}

LDDrift::Compile::~Compile() = default;
