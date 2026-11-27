/*
* Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */
#ifndef LUCID_DRIFT_EXCEPT_H
#define LUCID_DRIFT_EXCEPT_H
#include <string>
#define NULL_STRING "NULL_VALUE"

namespace LDDrift
{
    class Except
    {
    public: // constructors and destructor
        // default constructors : start
        Except();
        Except(const Except&);
        Except& operator=(const Except&);
        Except& operator=(Except&&) noexcept;
        Except(Except&&) noexcept;
        // default constructors : end

        // main constructors : start
        Except(const std::string& _program, const std::string& _message);
        Except(const std::string& _program, const std::string& _throwErrorFromLocation, const std::string& _message);
        // main constructors : end
        ~Except();

    public:
        std::string program;
        std::string message;
        std::string ErrorFromLocation;
    };
}
#endif
