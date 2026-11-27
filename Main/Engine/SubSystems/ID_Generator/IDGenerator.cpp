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

#include "IDGenerator.h"
#include <algorithm>

LDDrift::IDGenerator::IDGenerator() = default;

LDDrift::IDGenerator::~IDGenerator() = default;

std::uint32_t LDDrift::IDGenerator::GetMaxID() const {
    std::uint32_t maxID = 0;
    for (const auto& [id, Generation] : ActivatedIDs) {
        maxID = std::max(maxID, id);
    }
    return maxID;
}

std::uint32_t LDDrift::IDGenerator::GenerateID() {
    if (DeactivatedIDs.empty()) {
        const std::uint32_t newID = GetMaxID() + 1;
        ActivatedIDs.push_back({.id = newID, .Generation = 0});
        return newID;
    } else {
        auto [id, Generation] = DeactivatedIDs.front();
        DeactivatedIDs.pop();
        ActivatedIDs.push_back({.id = id, .Generation = Generation + 1});
        return id;
    }
}

void LDDrift::IDGenerator::DeactivateID(const std::uint32_t id) {
    if (const auto it = std::ranges::find(ActivatedIDs, id, &ID::id); it != ActivatedIDs.end()) {
        DeactivatedIDs.push({.id = it->id, .Generation = it->Generation});
        ActivatedIDs.erase(it);
    }
}
