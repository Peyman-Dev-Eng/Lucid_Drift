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

#ifndef LUCID_DRIFT_ID_GENERATOR_H
#define LUCID_DRIFT_ID_GENERATOR_H
#include <queue>
#include <unordered_set>
#include <cstdint>

namespace LDDrift
{
    struct ID
    {
        std::uint32_t id;
        std::uint32_t Generation;
    };

    class IDGenerator
    {
    private:
        [[nodiscard]] std::uint32_t GetMaxID() const;

    private:
        std::pmr::vector<ID> ActivatedIDs;
        std::queue<ID> DeactivatedIDs;

    public:
        IDGenerator();
        std::uint32_t GenerateID();
        void DeactivateID(std::uint32_t id);
        ~IDGenerator();
    };
} // LDDrift

#endif
