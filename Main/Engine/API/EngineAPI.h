#ifndef LUCID_DRIFT_ENGINE_API_H
#define LUCID_DRIFT_ENGINE_API_H
#ifdef __linux__
#include <dlfcn.h>
#elifdef _WIN32
#include <windows.h>
#endif
#include <ProjectWatchTower.h>
#include <functions.h>

namespace LDDrift::EngineAPI
{
    inline LDDrift::ProjectWatchTower* project_watch_tower = nullptr;
#ifdef __linux__
    inline void* handle = nullptr;
#endif
#ifdef _WIN32
    inline HMODULE hModule;
#endif
    void AfterCompileProject();
    void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* PWT_PTR);

    extern "C" {
    void BeginPlay();
    void Tick(float deltaTime = LDDrift::func::GetDeltaTime());
    void EndPlay();
    }


    void DestroyEngineAPI();
}

#endif
