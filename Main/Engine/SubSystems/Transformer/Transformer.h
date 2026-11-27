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

#ifndef LUCID_DRIFT_TRANSFORMER_H
#define LUCID_DRIFT_TRANSFORMER_H
#include <vector>
#include <VecPos2D.h>
#include <System/Window/Window.h>
#include <Actors/Line/Line.h>

namespace LDDrift
{
    namespace Actors
    {
        class Shape;
    }

    class Transformer
    {
    public:
        static int widthScreen;
        static int heightScreen;
        static int halfWidthScreen;
        static int halfHeightScreen;
        static std::pmr::vector<float> TransformToNDC_Position(const std::pmr::vector<float>&);
        static std::pmr::vector<float> TransformToGlobalPosition(const std::pmr::vector<float>&);
        static float TransformToNDC_Position(float pointPos, char posType);
        static float TransformToGlobalPosition(float pointPos, char posType);
        static std::pmr::vector<LDDrift::VecPos2D> TransformToNDC_Position(const LDDrift::Actors::Shape*);
        static std::pmr::vector<LDDrift::VecPos2D> TransformToGlobalPosition(const LDDrift::Actors::Shape*);
        static LDDrift::VecPos2D TransformToNDC_Position(const LDDrift::VecPos2D&);
        static LDDrift::VecPos2D TransformToGlobalPosition(const LDDrift::VecPos2D&);
        static std::pmr::vector<LDDrift::VecPos2D> TransformToNDC_Position(const std::pmr::vector<LDDrift::VecPos2D>&);
        static std::pmr::vector<LDDrift::VecPos2D> TransformToGlobalPosition(const std::pmr::vector<LDDrift::VecPos2D>&);
        static std::pmr::vector<LDDrift::Actors::Line::PNT> TransformToNDC_Position(
            const std::pmr::vector<LDDrift::Actors::Line::PNT>&);
        static std::pmr::vector<LDDrift::Actors::Line::PNT> TransformToGlobalPosition(
            const std::pmr::vector<LDDrift::Actors::Line::PNT>&);
    };
}

#endif
