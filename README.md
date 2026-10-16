# Lucid Drift.

**Lucid Drift** is a modern, experimental **2D game engine and editor** written in **C++26**.  
It focuses on clean architecture, low-level control over rendering, an integrated Dear ImGui-based editor, project management, and a simple runtime plugin system for game logic.

> **Current Status**  
> The engine is **not yet fully complete**. Many systems are still evolving and some features remain incomplete or experimental.  
> However, the core architecture, rendering pipeline, shape system, editor workflow, project management, and runtime API have reached a **stable and usable state**.  
> You can build the engine, create projects, edit shapes, compile game logic as a shared library, and run it through the `BeginPlay` / `Tick` / `EndPlay` lifecycle.

---

## Table of Contents

- [Highlights](#highlights)
- [Technology Stack & Requirements](#technology-stack--requirements)
- [Project Structure](#project-structure)
- [Architecture Overview](#architecture-overview)
- [Building the Engine](#building-the-engine)
  - [Linux](#linux)
  - [Windows](#windows)
- [Runtime Game API](#runtime-game-api)
- [Key Subsystems](#key-subsystems)
- [Development Status & Limitations](#development-status--limitations)
- [Troubleshooting](#troubleshooting)
- [Contributing & Feedback](#contributing--feedback)

---

## Highlights

- **Modern C++26** codebase with strong use of recent language features
- **OpenGL 4.6** renderer (GLSL 4.60) with custom vertex/fragment shaders
- **2D Shape System**: Circle, Polygon (convex & concave via triangulation), and Line
- **Dear ImGui Editor** for project exploration, shape editing, and code viewing
- **ProjectWatchTower** – file/folder management and project workflow
- **Built-in Compilation System** that compiles user game projects into shared libraries
- **Runtime Plugin API** – loads game logic as `.so` / `.dll` and calls `BeginPlay()`, `Tick(float)`, `EndPlay()`
- **Input System** with platform-specific keyboard & mouse handling
- **Point Hit Testing** and basic Transform utilities
- Modular design: Core, Window, Renderer, Scene, GUI, Compile, EngineAPI, etc.

---

## Technology Stack & Requirements

| Component              | Requirement / Version                          | Notes |
|------------------------|------------------------------------------------|-------|
| Language               | C++26                                          | Required |
| Build System           | CMake ≥ 4.3                                    | Declared in root `CMakeLists.txt` |
| Window / Context       | GLFW3                                          | Required |
| OpenGL Loader          | GLAD (included in repository)                  | OpenGL 4.6 core |
| GUI                    | Dear ImGui                                     | Must be placed in `ThirdParty/imgui` |
| Formatting             | fmt                                            | Required (`find_package(fmt REQUIRED)`) |
| Generator (recommended)| Ninja                                          | Optional but preferred on Linux |
| Graphics Driver        | OpenGL 4.6 + GLSL 4.60 capable                 | Critical |

**Platforms currently targeted**: Linux and Windows.

---
## Project Structure

```text
Lucid_Drift/
│
├── 📄 CMakeLists.txt
├── 📄 main.cpp
├── 📄 glad.c
│
├── 📁 glad/
│   └── 📁 include/glad/
│
├── 📁 Main/
│   ├── 📄 CMakeLists.txt
│   │
│   ├── 📁 Assertion/
│   │   └── Assertions
│   │
│   ├── 📁 EngineLibraries/
│   │   ├── 📁 Angle/
│   │   ├── 📁 ShapeData/
│   │   ├── 📁 VecColor/
│   │   └── 📁 VecPosition/
│   │
│   └── 📁 Engine/
│       │
│       ├── 📁 API/
│       │   └── EngineAPI                  # Runtime plugin system
│       │
│       ├── 📁 Actors/
│       │   ├── 📁 Line/
│       │   └── 📁 Shapes/
│       │       ├── 📁 MainShape/          # Base Shape
│       │       ├── 📁 Circle/
│       │       └── 📁 Polygon/
│       │
│       ├── 📁 Functions/
│       │
│       ├── 📁 Renderer/                   # OpenGL Renderer
│       │
│       ├── 📁 SubSystems/
│       │   ├── 📁 GUI_lOGIC/
│       │   ├── 📁 PointHitTesting/
│       │   ├── 📁 ProjectExplorer/        # ProjectWatchTower
│       │   ├── 📁 Transform/
│       │   └── 📁 WR_SettingSystem/
│       │
│       └── 📁 System/
│           ├── 📁 Compilation/            # Compile system
│           ├── 📁 Core/                   # Main engine coordinator
│           ├── 📁 GUI/                    # Dear ImGui
│           ├── 📁 Input/
│           ├── 📁 Scene/
│           ├── 📁 Triangulation/
│           └── 📁 Window/
│
└── 📁 ThirdParty/
    └── 📁 imgui/                          # Dear ImGui (must be added)
```
---

## Architecture Overview

The engine is built around a central **`Core`** class that owns and coordinates the major subsystems:

| Subsystem              | Responsibility |
|------------------------|----------------|
| **Core**               | Initialization, main loop (`Begin` + `EngineHandler`), lifetime management |
| **Window**             | GLFW window creation, fullscreen, viewport, clear color, callbacks |
| **Renderer**           | OpenGL resource management (VAO/VBO/shaders), shape & line batching, triangulation integration |
| **Scene**              | Holds and manages scene-level shapes |
| **GUI**                | Dear ImGui interface, editor windows, project explorer integration |
| **ProjectWatchTower**  | Project creation, file/folder browsing, path management |
| **Compile**            | Triggers and tracks compilation of user game projects |
| **EngineAPI**          | Dynamically loads the compiled game library and resolves `BeginPlay` / `Tick` / `EndPlay` |
| **Input**              | Platform-specific keyboard and mouse handling |
| **Triangulation**      | Converts polygons (including concave) into triangles for rendering |
| **PointHitTesting**    | Hit detection against shapes |
| **Transform**          | Basic transformation utilities |

All major components live under the `LDDrift` namespace.

---

## Building the Engine

### Prerequisites

1. A compiler with solid **C++26** support (recent GCC, Clang, or MSVC)
2. CMake ≥ 4.3
3. GLFW3 development package
4. fmt library
5. Dear ImGui sources placed in `ThirdParty/imgui` (and its backends)

### Linux

```bash
git clone https://github.com/Peyman-Dev-Eng/Lucid_Drift.git
cd Lucid_Drift

# Make sure Dear ImGui is present
# git submodule add https://github.com/ocornut/imgui.git ThirdParty/imgui
# or copy it manually

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel

# Run
./build/Lucid_Drift
```
---
###Windows
```bash
git clone https://github.com/Peyman-Dev-Eng/Lucid_Drift.git
cd Lucid_Drift

cmake -S . -B build
cmake --build build --config Debug --parallel

# Run (path depends on generator)
.\build\Debug\Lucid_Drift.exe
Note: Always check the root and Main/CMakeLists.txt for the exact targets and dependencies of the current branch.
Runtime Game API
Lucid Drift is designed so that game logic is compiled as a shared library and loaded at runtime.
Your game project must export three C-linkage functions:
#include <EngineAPI.h>   // or the appropriate header
```
---
#if defined(_WIN32)
    #define LUCID_DRIFT_GAME_EXPORT __declspec(dllexport)
#else
    #define LUCID_DRIFT_GAME_EXPORT __attribute__((visibility("default")))
#endif

extern "C" {

LUCID_DRIFT_GAME_EXPORT void BeginPlay()
{
    // Called once when gameplay starts
}

LUCID_DRIFT_GAME_EXPORT void Tick(float deltaTime)
{
    // Called every frame
    (void)deltaTime;
}

LUCID_DRIFT_GAME_EXPORT void EndPlay()
{
    // Called when gameplay ends
}

}
Important Rules
Function names must be exactly BeginPlay, Tick, and EndPlay
Must use extern "C"
Tick must take a float parameter
Build as a shared library (.so on Linux → expected name lib<ProjectName>.so, .dll on Windows)
Export symbols correctly (especially on Windows)
The engine loads the library after compilation and calls the lifecycle functions through the EngineAPI subsystem.
Key Subsystems
Shape System
Base Shape class
CircleShape
Polygon (supports both convex and concave via the Triangulation system)
Line
Renderer
Custom GLSL shaders
Batches shapes and lines into a single VBO
Supports filled and outline rendering modes
Rebuilds geometry when shapes change
Editor / GUI
Multiple dockable windows
Project explorer integration
Code buffer for viewing/editing
Console-like output redirection
Project & Compilation Pipeline
Create / open a project via ProjectWatchTower
Write game code
Trigger compilation from the editor
Engine loads the resulting shared library
Calls BeginPlay → game loop (Tick) → EndPlay
Development Status & Limitations
Lucid Drift has reached a stable foundation, but it is not a finished engine.
What is currently stable
Core architecture and main loop
Window + OpenGL context creation
Basic 2D shape rendering (Circle + Polygon)
Triangulation of polygons
Dear ImGui editor integration
Project file/folder management
Compilation triggering and shared-library loading
Runtime lifecycle API (BeginPlay / Tick / EndPlay)
Basic input handling
What is still incomplete / experimental
Full shape editing tools and property panels
Advanced transform system
Physics / collision (beyond basic point hit testing)
Camera system
Asset pipeline (textures, fonts, audio, etc.)
Serialization of scenes/projects
Cross-platform polish and packaging
Documentation of all internal APIs
Performance optimizations and batching improvements
Complete error handling and recovery paths
Expect breaking changes in internal APIs between commits. Treat this as a stable research / learning / experimental engine, not production-ready software.
Troubleshooting
Problem
Possible Solution
CMake cannot find GLFW / fmt
Install development packages or set CMAKE_PREFIX_PATH
OpenGL context creation fails
Ensure your GPU driver supports OpenGL 4.6
ImGui not found
Place Dear ImGui sources in ThirdParty/imgui
Game library loads but entry points missing
Check extern "C", exact function signatures, and export visibility
Build fails with C++26 features
Use a recent compiler (GCC 14+, Clang 18+, or latest MSVC)
Shapes not rendering
Check that shapes are added to the Renderer and triangulation succeeded
Contributing & Feedback
This is primarily a personal experimental project by Peyman-Dev-Eng.
Bug reports, architectural suggestions, and pull requests are welcome.
When reporting issues, please include:
Operating system
Compiler + CMake versions
Graphics driver / OpenGL version
Steps to reproduce
Relevant build or runtime logs
Lucid Drift — A lucid exploration of modern C++ game engine design.
Still growing. Already stable enough to drift.