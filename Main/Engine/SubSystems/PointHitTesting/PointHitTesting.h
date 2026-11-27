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

#ifndef LUCID_DRIFT_POINTHITTESTING_H
#define LUCID_DRIFT_POINTHITTESTING_H
#include <VecPos2D.h>
#include <vector>

namespace LDDrift
{
    class PointHitTesting final
    {
    private:
        static bool PointInValidRange(const LDDrift::VecPos2D&, const std::pair<LDDrift::VecPos2D, LDDrift::VecPos2D>&);

    public:
        static bool pointHitTesting(const LDDrift::VecPos2D&, const std::pmr::vector<LDDrift::VecPos2D>&);
    };
}

#endif
