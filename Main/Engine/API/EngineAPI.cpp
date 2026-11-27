/*
 * Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */

#include "EngineAPI.h"

namespace {
    LDDrift::Core* core;
}

void LDDrift::EngineAPI::AfterCompileProject() {
    std::string extension;
#ifdef __linux__
    extension = ".so";
#elifdef _WIN32
    extension = ".dll";
#endif

#ifdef __linux__
    if (handle != nullptr) {
        dlclose(handle);
    }
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

void LDDrift::EngineAPI::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::EngineAPI::ChangeSceneFunction(const LDDrift::ChangeSceneMode& mode) {
    core->sceneManager.ChangeScene(mode);
}

bool LDDrift::EngineAPI::AnimationIsPlayingFunction() {
    return core->sceneManager.HasPlayingAnimation();
}
