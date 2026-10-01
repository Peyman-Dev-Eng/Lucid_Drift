#ifndef LUCID_DRIFT_FUNCTIONS_H
#define LUCID_DRIFT_FUNCTIONS_H
#include <string>

namespace LDDrift::func
{
    constexpr std::string GetHostName() {
        std::string homeSystemName;
#ifdef _WIN32
        homeSystemName = std::getenv("COMPUTERNAME");
#elifdef __linux__
        homeSystemName = std::getenv("HOME");
#else
        homeSystemName = "";
#endif
        return homeSystemName;
    }
}

#endif
