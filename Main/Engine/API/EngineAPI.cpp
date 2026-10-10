#include "EngineAPI.h"

void LDDrift::EngineAPI::AfterCompileProject() {
    std::string extension;
#ifdef __linux__
    extension = ".so";
#elifdef _WIN32
    extension = ".dll";
#endif

#ifdef __linux__
    handle = dlopen((project_watch_tower->GetBuildFolderPath() / std::filesystem::path(
                        std::string("lib") + project_watch_tower->GetProjectName() + extension)).c_str(), RTLD_NOW);
    CTM_assert(handle != nullptr, dlerror())

    beginPlay = reinterpret_cast<BeginPlayFunction>(dlsym(handle, "BeginPlay"));
    tick = reinterpret_cast<TickFunction>(dlsym(handle, "Tick"));
    endPlay = reinterpret_cast<EndPlayFunction>(dlsym(handle, "EndPlay"));


#elifdef _WIN32
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
