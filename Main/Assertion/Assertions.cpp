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
