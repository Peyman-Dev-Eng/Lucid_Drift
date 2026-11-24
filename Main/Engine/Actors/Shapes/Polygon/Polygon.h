// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#ifndef LUCID_DRIFT_POLYGON_H
#define LUCID_DRIFT_POLYGON_H
#include "../MainShape/Shape.h"

namespace LDDrift::Actors
{
    class Polygon final : public LDDrift::Actors::Shape
    {
    public:
        Polygon();
        void Move(Dir direction) override;
        [[nodiscard]] LDDrift::VecCol CalculateAverageVertexColor() override;
        void Rebuild() override;
        void Rebuild(int, int) override;
        ~Polygon() override;
    };
}

#endif
