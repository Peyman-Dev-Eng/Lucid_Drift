#ifndef LUCID_DRIFT_FUNCTIONS_H
#define LUCID_DRIFT_FUNCTIONS_H
#include <filesystem>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "/home/Develepment/CLionProjects/Lucid_Drift/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

inline double lastTime;
inline double currentTime;
inline float deltaTime;

namespace LDDrift::func
{
    std::string GetHostName();
    std::filesystem::path GetExecutablePath();
    std::filesystem::path GetDefaultDiskPath();
    void InitDeltaTime();
    float GetDeltaTime();
}

#endif
