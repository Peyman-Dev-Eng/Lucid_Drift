#ifndef LUCID_DRIFT_FUNCTIONS_H
#define LUCID_DRIFT_FUNCTIONS_H
#include <filesystem>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif


namespace LDDrift::func
{
    std::string GetHostName();
    std::filesystem::path GetExecutablePath();
    std::filesystem::path GetDefaultDiskPath();
}

#endif
