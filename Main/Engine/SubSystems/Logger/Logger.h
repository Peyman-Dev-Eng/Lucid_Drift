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

#ifndef LUCID_DRIFT_LOGGER_H
#define LUCID_DRIFT_LOGGER_H
#define INFO "INFO"
#define DEBUG "DEBUG"
#define ERROR "ERROR"
#define WARNING "WARNING"
#include <string>
#include <chrono>
#include <filesystem>
#include <format>
#include <iomanip>

namespace LDDrift
{
    enum class LogType : unsigned long long int
    {
        Null = 0x00000000,
        GenTextureFailed = 0xA83F21B7,
        RenderSystem = 0x7D19C4E2,
        LoadShapeFailed = 0xB52E8A31,
        ImageReadFailed = 0x39F6D205,
        SystemInitFailed = 0xE71A4B93,
        SubSystemInitFailed = 0x6C82F1A5,
        PlayAnimationFailed = 0xD4937E28,
        FreeAnimationFailed = 0x21B8C6F4,
        ReadFileFailed = 0x95E3A712,
        WriteFileFailed = 0x4A7D2F86,
        LoadLibraryFileFailed = 0xF1829B43,
        CreateTextureFailed = 0x8B36D5E1,
        ChangeSceneFailed = 0x32C9A874,
        CreateNewSceneFailed = 0xC5E17B29,
        DeleteSceneFailed = 0x71A4E8D6,
        DeleteActorFailed = 0xE29B531C,
        CreateNewActorFailed = 0x5D83F2A7,
        CreateFileFailed = 0xB7C41965,
        PathNotAvailable = 0x2F96D3B8,
        ReadKeyboardInputEventFailed = 0xD8A2514E,
        ReadMouseInputEventFailed = 0x46E7B19C,
        CreateWindowFromGLFWFailed = 0x91A7C3E5,
        LoadImageFailed = 0xF4B8216D,
        ShapeTypeDetectionFailed = 0x63D9A2F8,
        InitCmakeFailed = 0xB1E75C39,
        FindActorFailed = 0x28C4D6A1,
        ZeroDivideFailed = 0xE6A193B4,
        OpenFileFailed = 0x7B52E8D3,
        FileHasNotBeenDetected = 0xC3F619A7,
        FileHasBeenDetected = 0x54A8D2E6,
        OpenFileSucceeded = 0x9D31B7F2,
        LoadImageSucceeded = 0x16E4C8A9,
        CreateNewActorSucceeded = 0xA2F735D1,
        DeleteActorSucceeded = 0x38B9E4C7,
        ReadFileSucceeded = 0xD1A65B83,
        WriteFileSucceeded = 0x82E3F197,
        PathIsAvailable = 0x4F7A2D68,
        FindLineJoiningAlgorithmFailed = 0xE8C215A4,
        TriangulateFailed = 0x5A93D7B1,
        FoundSceneTargetFailed = 0xB6E14C82,
        FoundSceneTargetSucceeded = 0x73D8A5F6,
        CompileOpenGLShaderSourceFailed,
        LinkOpenGLProgramFailed,
        CompileOpenGLShaderSourceSucceeded,
        LinkOpenGLProgramSucceeded,

    };

    class Log final
    {
    public:
        struct LOG_STRUCT
        {
            LogType log_type;
            std::string log;
        };

        LOG_STRUCT log_;

    public:
        Log();
        explicit Log(const std::string& msg, const LogType& LOG_TYPE);
        ~Log();
        [[nodiscard]] LOG_STRUCT GetLog() const;
    };

    class Logger final
    {
    public:
        Logger();
        ~Logger();
        static void InfoLog(const std::string& fromProgram, const std::string& systemEngineLog, const Log& log);
        static void DebugLog(const std::string& fromProgram, const std::string& systemEngineLog,
                             const Log& log);
        static void ErrorLog(const std::string& fromProgram, const std::string& systemEngineLog,
                             const Log& log);
        static void WarningLog(const std::string& fromProgram, const std::string& systemEngineLog,
                               const Log& log);
    };
}
#endif
