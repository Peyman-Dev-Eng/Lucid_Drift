#include "Compile.h"

LDDrift::Compile::Compile() = default;

void LDDrift::Compile::init(LDDrift::ProjectWatchTower* projectWatchTowerPTR) {
    projectWatchTower = projectWatchTowerPTR;
}

bool LDDrift::Compile::BuildProject()
{
    if (buildStatus.load() == CompileBuildStatus::Building)
    {
        errorLog =
            "Your project is already being built. "
            "Starting another build now would only duplicate work.";

        return false;
    }

    // Join the previous build thread if it has finished.
    if (compileProjectThread.joinable())
    {
        compileProjectThread.join();
    }

    const std::filesystem::path buildPath =
        std::filesystem::absolute(projectWatchTower->GetProjectPath() / "BUILD");

    const std::string command =
        "cmake --build \"" + buildPath.string() +
        "\" --parallel 14";

    buildStatus.store(CompileBuildStatus::Building);

    compileProjectThread = std::thread([this, command]()
    {
        if (const int result = std::system(command.c_str()); result == 0)
        {
            buildStatus.store(
                CompileBuildStatus::Succeeded,
                std::memory_order_release
            );
        }
        else
        {
            buildStatus.store(
                CompileBuildStatus::Failed,
                std::memory_order_release
            );
        }
    });

    return true;
}

const std::string& LDDrift::Compile::GetErrorLog() const {
    return errorLog;
}

LDDrift::CompileBuildStatus LDDrift::Compile::GetStatus() const {
    return buildStatus.load(std::memory_order_acquire);
}

LDDrift::Compile::~Compile() {
    if (compileProjectThread.joinable()) {
        compileProjectThread.join();
    }
}
