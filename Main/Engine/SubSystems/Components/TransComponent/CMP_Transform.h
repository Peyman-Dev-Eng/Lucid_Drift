// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#ifndef LUCID_DRIFT_CMP_TRANSFORMER_H
#define LUCID_DRIFT_CMP_TRANSFORMER_H
#include <Angle.h>
#include <vector>
#include <VecPos2D.h>


namespace LDDrift
{
    class CMP_Transform
    {
    public:
        struct Scale
        {
            float x = 1.0f;
            float y = 1.0f;
        };

    private:
        // data
        std::pmr::vector<LDDrift::VecPos2D> points;
        // main data
        Scale scale;
        LDDrift::Angle rotation = 0;
        LDDrift::VecPos2D translation {0,0};

    public:
        CMP_Transform();
        void SetRotation(const LDDrift::Angle& Rotation_);
        void SetScale(const Scale& Scale_);
        void SetPoints(const std::pmr::vector<LDDrift::VecPos2D>& Points_);
        void SetTranslation(const LDDrift::VecPos2D& Translation_);
        void Calculate();
        ~CMP_Transform();
    };
}


#endif
