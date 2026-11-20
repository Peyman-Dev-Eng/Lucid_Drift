#ifndef LUCID_DRIFT_LOGGER_H
#define LUCID_DRIFT_LOGGER_H
#define INFO "INFO"
#define DEBUG "DEBUG"
#define ERROR "ERROR"
#define WARNING "WARNING"
#include <string>
#include <chrono>
#include <format>
#include <iomanip>

namespace LDDrift
{
    inline std::size_t logNumber = 0;

    class Logger
    {
    public:
        Logger();
        ~Logger();
        static void InfoLog(const std::string& systemEngineLog, const std::string& log);
        static void DebugLog(const std::string& systemEngineLog, const std::string& log);
        static void ErrorLog(const std::string& systemEngineLog, const std::string& log);
        static void WarningLog(const std::string& systemEngineLog, const std::string& log);
    };
}

#endif
