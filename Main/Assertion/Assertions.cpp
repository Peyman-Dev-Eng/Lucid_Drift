#include "Assertions.h"


void LDDrift::Assertions::PrintLog(const char* condition, const char* file, int line, const char* function, const char* message) {
    // print detail
    std::cerr << RED << "Assertion failed: " << condition << "   |   " << "in file: " << file << "   |   "
        << "in line: " << line << "   |   " << "target function: " << function << RESET << std::endl;

    // print message
    message != nullptr ? std::cerr << RED << "Message: " << message << RESET << std::endl : std::cerr << "";

    std::abort();
}
