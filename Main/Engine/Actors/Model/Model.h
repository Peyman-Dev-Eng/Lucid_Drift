// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#ifndef LUCID_DRIFT_MODEL_H
#define LUCID_DRIFT_MODEL_H
#include <type_traits>
#include <cgltf.h>
#include <vector>
#include <VecPos2D.h>
#include <VecPos3D.h>

namespace LDDrift
{
    class Model
    {
    private:
        struct vertex
        {
            LDDrift::VecPos2D position;
            LDDrift::VecPos3D normal;
            LDDrift::VecPos2D texCoord;
        };
        std::vector<vertex> vertices;
        std::vector<std::size_t> indices;

    public:
        Model();
        ~Model();
    };
}

#endif
