#ifndef LUCID_DRIFT_COMPILE_H
#define LUCID_DRIFT_COMPILE_H
#include <filesystem>
#include <string>
#include <atomic>
#include <thread>
#include <ProjectWatchTower.h>

namespace LDDrift
{
    enum class CompileBuildStatus
    {
        Idle,
        Building,
        Succeeded,
        Failed
    };

    class Compile
    {
    private:
        std::atomic<CompileBuildStatus> buildStatus;
        std::atomic_bool isUserProjectCompiling{false};
        std::atomic_int buildExitCode{-1};
        std::string errorLog;
        LDDrift::ProjectWatchTower* projectWatchTower = nullptr;
        std::thread compileProjectThread;

    public:
        Compile();
        void init(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        bool BuildProject();
        [[nodiscard]] const std::string& GetErrorLog() const;
        [[nodiscard]] CompileBuildStatus GetStatus() const;
        ~Compile();
    };
}

#endif
