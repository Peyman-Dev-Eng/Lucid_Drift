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

#include "Compile.h"

namespace
{
    struct CommandResult
    {
        std::string output;
        int exitCode = -1;
    };

    CommandResult RunCommand(const std::string& command) {
        CommandResult result;
        std::array<char, 4096> buffer{};

        FILE* pipe = popen((command + " 2>&1").c_str(), "r");
        if (!pipe) {
            result.output = "Failed to execute command: " + command;
            return result;
        }

        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
            result.output += buffer.data();
        }

        if (const int status = pclose(pipe); WIFEXITED(status)) {
            result.exitCode = WEXITSTATUS(status);
        } else {
            result.exitCode = status;
        }
        return result;
    }

    std::pmr::vector<LDDrift::Compile::CompileError> ParseErrors(const std::string& output) {
        std::pmr::vector<LDDrift::Compile::CompileError> errors;
        std::istringstream stream(output);
        std::string line;

        // الگو: path:line:col: error: message
        // یا:   path:line:col: warning: message
        static const std::regex pattern(
            R"(^([^:]+):(\d+):(\d+):\s+(error|warning|note):\s+(.*)$)"
        );

        std::smatch match;
        while (std::getline(stream, line)) {
            if (std::regex_match(line, match, pattern)) {
                LDDrift::Compile::CompileError e;
                e.file = match[1].str();
                e.line = std::stoi(match[2].str());
                e.column = std::stoi(match[3].str());
                e.severity = match[4].str();
                e.message = match[5].str();
                errors.push_back(std::move(e));
            }
        }
        return errors;
    }
}


LDDrift::Compile::Compile() = default;

void LDDrift::Compile::init(LDDrift::ProjectWatchTower* projectWatchTowerPTR) {
    projectWatchTower = projectWatchTowerPTR;
}

bool LDDrift::Compile::BuildProject() {
    if (buildStatus.load() == CompileBuildStatus::Building) {
        LDDrift::Logger::WarningLog("Engine", "Compile", Log("Build already in progress.", LogType::Null));
        return false;
    }

    if (compileProjectThread.joinable()) {
        compileProjectThread.join();
    }

    const std::filesystem::path projectPath =
        absolute(projectWatchTower->GetProjectPath());

    const std::filesystem::path buildPath =
        absolute(projectPath / "BUILD");

    const std::string configureCommand =
        "cmake -S \"" + projectPath.string() +
        "\" -B \"" + buildPath.string() +
        "\" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON";

    const std::string buildCommand =
        "cmake --build \"" + buildPath.string() +
        "\" --parallel 14";

    buildStatus.store(CompileBuildStatus::Building, std::memory_order_release);

    compileProjectThread = std::thread(
        [this, configureCommand, buildCommand]()
        {
            auto [output, exitCode] = RunCommand(configureCommand);


            if (exitCode == 0) {
                auto [OutPut, EXIT_CODE] = RunCommand(buildCommand);

                if (!output.empty() && !OutPut.empty()) {
                    output += '\n';
                }

                output += OutPut;
                exitCode = EXIT_CODE;
            }

            {
                auto errors = ParseErrors(output);
                std::lock_guard<std::mutex> lock(errorMutex);
                errorLog = output;
                compileErrors = std::move(errors);
            }

            if (exitCode == 0) {
                buildStatus.store(
                    CompileBuildStatus::Succeeded,
                    std::memory_order_release
                );
            } else {
                buildStatus.store(
                    CompileBuildStatus::Failed,
                    std::memory_order_release
                );
            }
        }
    );

    return true;
}

std::pmr::vector<LDDrift::Compile::CompileError> LDDrift::Compile::GetErrorLog() const {
    std::lock_guard<std::mutex> lock(errorMutex);
    return compileErrors;
}

LDDrift::CompileBuildStatus LDDrift::Compile::GetStatus() const {
    return buildStatus.load(std::memory_order_acquire);
}

LDDrift::Compile::~Compile() {
    if (compileProjectThread.joinable()) {
        compileProjectThread.join();
    }
}
