// Copyright (C) 2026 Peyman
//
// This file is part of Lucid Drift.
// Lucid Drift is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// This software is distributed without any warranty.
// See the LICENSE file for the full license text.
// See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.

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
#include <System/Core/Core.h>

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

    // user functions
    void ChangeSceneFunction(const LDDrift::ChangeSceneMode& mode);
    bool AnimationIsPlayingFunction();

}

#endif
