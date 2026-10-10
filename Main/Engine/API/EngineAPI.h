#ifndef LUCID_DRIFT_ENGINE_API_H
#define LUCID_DRIFT_ENGINE_API_H
#if defined(_WIN32)
#if defined(LD_PLUGIN_BUILD)
#define LD_PLUGIN_API __declspec(dllexport)
#else
#define LD_PLUGIN_API
#endif
#else
#define LD_PLUGIN_API __attribute__((visibility("default")))
#endif
#ifdef __linux__
#include <dlfcn.h>
#elifdef _WIN32
#include <windows.h>
#endif
#include "ProjectWatchTower.h"
#include <functions.h>

namespace LDDrift::EngineAPI
{
    inline LDDrift::ProjectWatchTower* project_watch_tower = nullptr;
    using BeginPlayFunction = void (*)();
    using TickFunction = void (*)(float);
    using EndPlayFunction = void (*)();


    inline BeginPlayFunction beginPlay;
    inline TickFunction tick;
    inline EndPlayFunction endPlay;


#ifdef __linux__
    inline void* handle = nullptr;
#endif
#ifdef _WIN32
    inline HMODULE hModule;
#endif
    void AfterCompileProject();
    void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* PWT_PTR);

    extern "C" {
    LD_PLUGIN_API void BeginPlay();
    LD_PLUGIN_API void Tick(float deltaTime);
    LD_PLUGIN_API void EndPlay();
    }


    void DestroyEngineAPI();
}

#endif
