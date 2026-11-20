#include "Logger.h"

#include <iostream>

LDDrift::Logger::Logger() = default;

LDDrift::Logger::~Logger() = default;

void LDDrift::Logger::InfoLog(const std::string& systemEngineLog, const std::string& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout
        << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
        << "] [" << systemEngineLog << "] [" << INFO << "] " << log << '\n';
}

void LDDrift::Logger::DebugLog(const std::string& systemEngineLog, const std::string& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout
        << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
        << "] [" << systemEngineLog << "] [" << DEBUG << "] " << log << '\n';
}

void LDDrift::Logger::ErrorLog(const std::string& systemEngineLog, const std::string& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout
        << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
        << "] [" << systemEngineLog << "] [" << ERROR << "] " << log << '\n';
}

void LDDrift::Logger::WarningLog(const std::string& systemEngineLog, const std::string& log) {
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout
        << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
        << "] [" << systemEngineLog << "] [" << WARNING << "] " << log << '\n';
}
