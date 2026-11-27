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

#ifndef LUCID_DRIFT_MAIN_RENDERER_H
#define LUCID_DRIFT_MAIN_RENDERER_H
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Line/Line.h>
#include "Actors/Texture/Texture.h"
#include <vector>

namespace LDDrift
{
    class Core;

    class MainRenderer
    {
    private:
        LDDrift::Core* core = nullptr;

    public :
        MainRenderer();
        ~MainRenderer();
        static void StaticDrawer(const LDDrift::Core* _core,
                                 const std::pmr::vector<LDDrift::Actors::Shape*>& shapes,
                                 const std::pmr::vector<LDDrift::Actors::Line*>& lines);
        static void StaticDrawer(const LDDrift::Core* _core, const std::pmr::vector<LDDrift::Actors::Texture*>& textures);
        void SetCorePTR(LDDrift::Core* core_ptr);
        [[nodiscard]] glm::mat4 UpdateViewMatrix() const;
    };
} // LDDrift

#endif
