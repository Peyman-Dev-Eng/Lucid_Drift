#include "EngineAPI.h"

void LDDrift::EngineAPI::AfterCompileProject() {
#ifdef __linux__
    handle = dlopen(project_watch_tower->GetBuildFolderPath().c_str(), RTLD_NOW);
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
    dlclose(handle);
#elifdef _WIN32
#endif
}
