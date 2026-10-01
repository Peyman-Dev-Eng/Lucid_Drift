#include "functions.h"

std::string LDDrift::func::GetHostName() {
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

std::filesystem::path LDDrift::func::GetExecutablePath() {
    return std::filesystem::read_symlink("/proc/self/exe");
}
