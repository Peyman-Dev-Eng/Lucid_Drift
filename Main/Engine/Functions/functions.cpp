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

#include "functions.h"

std::string LDDrift::func::GetHostName() {
    std::string homeSystemName;
#ifdef _WIN32
    homeSystemName = std::getenv("USERPROFILE");
#elifdef __linux__
    homeSystemName = std::getenv("HOME");
#else
    homeSystemName = "";
#endif
    return homeSystemName;
}

std::filesystem::path LDDrift::func::GetExecutablePath() {
    return std::filesystem::read_symlink("/proc/self/exe");
}

std::filesystem::path LDDrift::func::GetDefaultDiskPath() {
    std::filesystem::path defaultPath;
#ifdef _WIN32
    PWSTR path = nullptr;

    const HRESULT result = SHGetKnownFolderPath(
        FOLDERID_Desktop,
        0,
        nullptr,
        &path
    );

    if (FAILED(result)) {
        throw std::runtime_error("Failed to get Desktop path.");
    }

    std::filesystem::path desktopPath(path);

    CoTaskMemFree(path);

    return desktopPath;
#elifdef __linux__
    defaultPath = std::getenv("HOME");
#else
    defaultPath = "";
#endif
    return defaultPath;
}

void LDDrift::func::InitDeltaTime() {
    lastTime = glfwGetTime();
}

void LDDrift::func::TickDeltaTime() {
    currentTime = glfwGetTime();
    deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
}

float LDDrift::func::GetDeltaTime() {
    return deltaTime;
}
