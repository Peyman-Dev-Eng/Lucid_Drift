#ifndef LUCID_DRIFT_COMPILE_H
#define LUCID_DRIFT_COMPILE_H
#include <filesystem>
#include <string>
#include <atomic>
#include <thread>
#include <ProjectWatchTower.h>
#include <cstdio>
#include <mutex>
#include <sstream>
#include <regex>
#include <sys/wait.h>

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
    public:
        struct CompileError
        {
            std::string file;
            int line = 0;
            int column = 0;
            std::string severity;
            std::string message;
        };

    private:
        std::atomic<CompileBuildStatus> buildStatus;
        std::atomic_bool isUserProjectCompiling{false};
        std::atomic_int buildExitCode{-1};
        std::string errorLog;
        LDDrift::ProjectWatchTower* projectWatchTower = nullptr;
        std::thread compileProjectThread;
        std::vector<CompileError> compileErrors;
        mutable std::mutex errorMutex;

    public:
        Compile();
        void init(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        bool BuildProject();
        [[nodiscard]] std::vector<CompileError> GetErrorLog() const;
        [[nodiscard]] CompileBuildStatus GetStatus() const;
        ~Compile();
    };
}

#endif
