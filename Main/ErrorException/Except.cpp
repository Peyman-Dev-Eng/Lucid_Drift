// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

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
