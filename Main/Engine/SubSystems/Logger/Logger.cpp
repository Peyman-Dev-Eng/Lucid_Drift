#include "Logger.h"

#include <complex>
#include <iostream>

LDDrift::Log::Log() = default;

LDDrift::Log::Log(const std::string& msg, const LogType& LOG_TYPE) {
    log_.log = msg;
    log_.log_type = LOG_TYPE;
}

LDDrift::Log::~Log() = default;

LDDrift::Log::LOG_STRUCT LDDrift::Log::GetLog() const {
    return log_;
}

LDDrift::Logger::Logger() = default;

LDDrift::Logger::~Logger() = default;

void LDDrift::Logger::InfoLog(const std::string& fromProgram, const std::string& systemEngineLog,
                              const Log& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto [log_type, message] = log.GetLog();
    std::cout
        << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
        << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << INFO << "] " << message << '\n';
}

void LDDrift::Logger::DebugLog(const std::string& fromProgram, const std::string& systemEngineLog,
                               const Log& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (auto [log_type, message] = log.GetLog(); log_type == Log::LogType::Null)
        std::cout
            << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
            << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << DEBUG << "] " << message << '\n';
    else
        std::cout
            << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
            << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << DEBUG << "] ["
            << static_cast<unsigned long long int>(log_type) << "] " << message << '\n';
}

void LDDrift::Logger::ErrorLog(const std::string& fromProgram, const std::string& systemEngineLog,
                               const Log& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (auto [log_type, message] = log.GetLog(); log_type == Log::LogType::Null)
        std::cout
            << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
            << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << ERROR << "] " << message << '\n';
    else
        std::cout
            << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
            << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << ERROR << "] ["
            << static_cast<unsigned long long int>(log_type) << "] " << message << '\n';
}

void LDDrift::Logger::WarningLog(const std::string& fromProgram, const std::string& systemEngineLog,
                                 const Log& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (auto [log_type, message] = log.GetLog(); log_type == Log::LogType::Null)
        std::cout
            << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
            << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << WARNING << "] " << message << '\n';
    else
        std::cout
            << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
            << "]" << " [" << fromProgram << "] [" << systemEngineLog << "] [" << WARNING << "] ["
            << static_cast<unsigned long long int>(log_type) << "] " << message << '\n';
}
