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

#ifndef LUCID_DRIFT_CORE_H
#define LUCID_DRIFT_CORE_H

// standard C++ library include
#include <chrono>
#include <string>
#include <thread>
#include <vector>

// engine files include
#include <WR_SettingSystem.h>
#include "API/EngineAPI.h"
#include <Actors/Line/Line.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <CodePathfinder.h>
#include <GUI.h>
#include <Renderer/ShapeRender/ShapeRender.h>
#include <SubSystems/PointHitTesting/PointHitTesting.h>
#include <SubSystems/ProjectExplorer/ProjectWatchTower.h>
#include <System/Camera/Camera.h>
#include <Renderer/Communicator/MainRenderer.h>
#include <System/Input/input.h>
#include <System/Scene/Scene.h>
#include <System/Triangulation/Triangulation.h>
#include <System/Window/Window.h>
#include <sstream>
#include <Actors/Texture/Texture.h>
#include <Renderer/TextureRender/TextureRender.h>
#include <streambuf>
#include <System/SceneManager/MainSceneManager/SceneManager.h>

namespace LDDrift
{
    class Core final
    {
    private:
        void InitCore();
        void RunEngineFrame();
        void RunGameFrame();

        void CameraController();

    public:
        std::stringstream consoleBuffer;
        std::streambuf* oldC_outBuf = nullptr;
        bool engineRun = true;

    public:
        // data
        LDDrift::Camera camera;
        LDDrift::Window window;
        LDDrift::ShapeRender shape_render;
        LDDrift::ProjectWatchTower projectWatchTower;
        LDDrift::PointHitTesting pointHitTesting;
        LDDrift::GUI gui;
        LDDrift::Compile compile;
        LDDrift::CodePathfinder codePathfinder;
        LDDrift::UserProjectSetting userProjectSetting;
        LDDrift::WR_SettingSystem Write_Read_UserProjectSetting;
        LDDrift::TextureRender textureRender;
        LDDrift::MainRenderer mainRenderer;
        LDDrift::SceneManager sceneManager;

        // functions
        explicit Core();
        void Begin();
        void EngineHandler();
        void End() const;
        ~Core();
    }; // class Core
} // namespace LDDrift

#endif
