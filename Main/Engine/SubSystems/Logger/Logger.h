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
        CreateWindowFromGLFW_ToFailed,
        LoadImageFailed,
        ShapeTypeDetectionFailed,
        InitCmakeFailed,
        FindActorFailed,
        ZeroDivideFailed,
        OpenFileFailed,
        FileHasNotBeenDetected,
        FileHasBeenDetected,
        OpenFileSucceeded,
        LoadImageSucceeded,
        CreateNewActorSucceeded,
        DeleteActorSucceeded,
        ReadFileSucceeded,
        WriteFileSucceeded,
        PathIsAvailable,
        FindLineJoiningAlgorithmFailed,
        TriangulateFailed,
        FoundSceneTargetFailed,
        FoundSceneTargetSucceeded,
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
