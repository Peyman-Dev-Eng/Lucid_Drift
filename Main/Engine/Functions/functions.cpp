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

    if (FAILED(result))
    {
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

float LDDrift::func::GetDeltaTime() {
    currentTime = glfwGetTime();
    deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
    return deltaTime;
}
