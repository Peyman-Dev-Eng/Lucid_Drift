#include <iostream>
#include <thread>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Assertions.h"
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "SubSystems/PointHitTesting/PointHitTesting.h"
#include <System/Triangulation/Triangulation.h>
#include <System/Window/Window.h>
#include <Renderer/Renderer.h>
#include <ProjectWatchTower.h>
#include <System/Input/input.h>
#include <System/GUI/GUI.h>
#include <System/Core/Core.h>
#include <SubSystems/Transform/Transform.h>


int main() {
    LDDrift::Core core;
    core.Begin();
    core.EngineHandler();
    return 0;
}
