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

namespace LDDrift
{
    class Core
    {
    private:
        void InitCore();
    public:
        std::stringstream consoleBuffer;
        std::streambuf* oldC_outBuf = nullptr;
        LDDrift::Actors::Circle* circle = nullptr;

    public:
        // data
        LDDrift::Window window;
        LDDrift::Renderer render;
        LDDrift::ProjectWatchTower projectWatchTower;
        LDDrift::PointHitTesting pointHitTesting;
        LDDrift::GUI gui;

        // functions
        explicit Core();
        void Begin();
        void EngineHandler();
        ~Core();
    };
}

#endif
