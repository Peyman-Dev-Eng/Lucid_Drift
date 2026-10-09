#include "EngineAPI.h"

void LDDrift::EngineAPI::AfterCompileProject() {
#ifdef __linux__
    handle = dlopen(
        static_cast<std::string>(project_watch_tower->GetBuildFolderPath().string() + '/' +
            project_watch_tower->GetProjectName() + ".so").c_str(), RTLD_NOW);
    CTM_assert(handle != nullptr, dlerror())

#elifdef _WIN32
    hModule = LoadLibraryA(project_watch_tower->GetBuildFolderPath().c_str());
#endif
}

void LDDrift::EngineAPI::SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* PWT_PTR) {
    project_watch_tower = PWT_PTR;
}

void LDDrift::EngineAPI::DestroyEngineAPI() {
#ifdef __linux__
    if (handle != nullptr)
        dlclose(handle);
#elifdef _WIN32
    FreeLibrary(hModule);
#endif
}
