#ifndef LUCID_DRIFT_CORE_H
#define LUCID_DRIFT_CORE_H

// standard C++ library include
#include <vector>
#include <string>
#include <thread>
#include <chrono>

// engine files include
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <System/Input/input.h>
#include <System/Window/Window.h>
#include <GUI.h>
#include <System/Triangulation/Triangulation.h>
#include <Renderer/Renderer.h>
#include <SubSystems/PointHitTesting/PointHitTesting.h>
#include <SubSystems/ProjectExplorer/ProjectWatchTower.h>
#include <sstream>
#include <streambuf>
#include "API/EngineAPI.h"
#include <System/Scene/Scene.h>
#include <CodePathfinder.h>
#include <System/Camera/Camera.h>

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
        LDDrift::Renderer render;
        LDDrift::ProjectWatchTower projectWatchTower;
        LDDrift::PointHitTesting pointHitTesting;
        LDDrift::GUI gui;
        LDDrift::Compile compile;
        LDDrift::Scene scene;
        LDDrift::CodePathfinder codePathfinder;

        // functions
        explicit Core();
        void Begin();
        void EngineHandler();
        ~Core();
    };

    namespace func
    {
        LDDrift::Scene* GetSceneObjectPointer();
        LDDrift::Camera* GetCameraObjectPointer();
    }
}

#endif
