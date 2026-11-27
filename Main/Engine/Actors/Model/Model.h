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
        std::pmr::vector<vertex> vertices;
        std::pmr::vector<std::size_t> indices;

    public:
        Model();
        ~Model();
    };
}

#endif
