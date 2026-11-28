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

#ifndef LUCID_DRIFT_CMP_COLLIDER_H
#define LUCID_DRIFT_CMP_COLLIDER_H
#include <thread>
#include <vector>
#include <VecPos2D.h>
#include <type_traits>

namespace LDDrift
{
    class CMP_Collider
    {
    public:
        std::pmr::vector<LDDrift::VecPos2D> normals;
        std::pmr::vector<LDDrift::VecPos2D> BoundingBox; // vertices of rectangle

    private:
        bool Active = true;
        bool Loaded = false;

    public:
        CMP_Collider();
        void Load(const std::pmr::vector<LDDrift::VecPos2D>& vertices);
        void unLoad();
        void SetActive(bool active_);
        ~CMP_Collider();
    };
} // LDDrift

#endif
