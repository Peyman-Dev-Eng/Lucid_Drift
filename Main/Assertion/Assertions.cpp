#include "Assertions.h"


void PrintLog(const char* condition, const char* file, int line, const char* function, const char* message) {
    // print detail
    std::cerr << "Assertion failed: " << condition << "   |   " << "in file: " << file << "   |   "
        << "in line: " << line << "   |   " << "target function: " << function << std::endl;

    // print message
    message != nullptr ? std::cerr << "Message: " << message << std::endl : std::cerr << "";

    std::abort();
}
