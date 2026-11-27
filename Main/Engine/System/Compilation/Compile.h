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
#include <Logger.h>

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
        std::pmr::vector<CompileError> compileErrors;
        mutable std::mutex errorMutex;

    public:
        Compile();
        void init(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        bool BuildProject();
        [[nodiscard]] std::pmr::vector<CompileError> GetErrorLog() const;
        [[nodiscard]] CompileBuildStatus GetStatus() const;
        ~Compile();
    };
}

#endif
