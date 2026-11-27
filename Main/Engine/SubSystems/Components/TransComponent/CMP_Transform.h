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
