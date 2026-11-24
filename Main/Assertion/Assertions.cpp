// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#include "Assertions.h"


void LDDrift::Assertions::PrintLog(const char* condition, const char* file, const int line, const char* function,
                                   const char* message) {
    // print detail
    std::cerr << RED << "Assertion failed: " << condition << "   |   " << "in file: " << file << "   |   "
        << "in line: " << line << "   |   " << "target function: " << function << RESET << std::endl;

    // print message
    message != nullptr ? std::cerr << RED << "Message: " << message << RESET << std::endl : std::cerr << "";
    std::abort();
}
