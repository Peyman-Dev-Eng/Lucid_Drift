#ifndef LUCID_DRIFT_FUNCTIONS_H
#define LUCID_DRIFT_FUNCTIONS_H
#include <filesystem>
#include <string>

namespace LDDrift::func
{
    std::string GetHostName();
    std::filesystem::path GetExecutablePath();
}

#endif
