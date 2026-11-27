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

#include "Except.h"

LDDrift::Except::Except() = default;

LDDrift::Except::~Except() = default;

LDDrift::Except::Except(const Except& other) {
    this->program = other.program;
    this->message = other.message;
    this->ErrorFromLocation = other.ErrorFromLocation;
}

LDDrift::Except::Except(Except&& other) noexcept {
    *this = std::move(other);
}

LDDrift::Except::Except(const std::string& _program, const std::string& _message) {
    program = _program;
    message = _message;
    ErrorFromLocation = NULL_STRING;
}

LDDrift::Except::Except(const std::string& _program, const std::string& _throwErrorFromLocation,
                        const std::string& _message) {
    program = _program;
    message = _message;
    ErrorFromLocation = _throwErrorFromLocation;
}

LDDrift::Except& LDDrift::Except::operator=(Except&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    program = std::move(other.program);
    message = std::move(other.message);
    ErrorFromLocation = std::move(other.ErrorFromLocation);
    return *this;
}

LDDrift::Except& LDDrift::Except::operator=(const Except& other) = default;
