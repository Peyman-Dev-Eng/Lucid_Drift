// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

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
        static std::vector<float> TransformToNDC_Position(const std::vector<float>&);
        static std::vector<float> TransformToGlobalPosition(const std::vector<float>&);
        static float TransformToNDC_Position(float pointPos, char posType);
        static float TransformToGlobalPosition(float pointPos, char posType);
        static std::vector<LDDrift::VecPos2D> TransformToNDC_Position(const LDDrift::Actors::Shape*);
        static std::vector<LDDrift::VecPos2D> TransformToGlobalPosition(const LDDrift::Actors::Shape*);
        static LDDrift::VecPos2D TransformToNDC_Position(const LDDrift::VecPos2D&);
        static LDDrift::VecPos2D TransformToGlobalPosition(const LDDrift::VecPos2D&);
        static std::vector<LDDrift::VecPos2D> TransformToNDC_Position(const std::vector<LDDrift::VecPos2D>&);
        static std::vector<LDDrift::VecPos2D> TransformToGlobalPosition(const std::vector<LDDrift::VecPos2D>&);
        static std::vector<LDDrift::Actors::Line::PNT> TransformToNDC_Position(
            const std::vector<LDDrift::Actors::Line::PNT>&);
        static std::vector<LDDrift::Actors::Line::PNT> TransformToGlobalPosition(
            const std::vector<LDDrift::Actors::Line::PNT>&);
    };
}

#endif
