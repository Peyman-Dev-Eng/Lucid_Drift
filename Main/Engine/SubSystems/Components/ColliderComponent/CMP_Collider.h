// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#ifndef LUCID_DRIFT_CMP_COLLIDER_H
#define LUCID_DRIFT_CMP_COLLIDER_H
#include <vector>
#include <VecPos2D.h>
#include <type_traits>

namespace LDDrift
{
    class CMP_Collider
    {
    private:
        std::pmr::vector<LDDrift::VecPos2D> normals;
        std::pmr::vector<LDDrift::VecPos2D> BoundingBox; // vertices of rectangle

    public:
        CMP_Collider();
        void Initialize();
        ~CMP_Collider();
    };
} // LDDrift

#endif
