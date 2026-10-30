<div align="center">

# 🌊 Lucid Drift

<img src="docs/images/lucid-drift-banner.png" alt="Lucid Drift — abstract 2D geometry and rendering banner" width="100%">

### *A free-flowing stream of imagination — with the clarity to build your own world.*

### *WARNING: only runs on Linux ـ I develop Lucid Drift primarily on Linux.  
If you work on Windows and would like to help make the engine run properly on that platform (build system, module loading, OpenGL context, input, etc.), I warmly welcome collaboration.  
Pull requests, testing feedback, and platform-specific fixes are all appreciated.*

**A native C++ game-engine project exploring the foundations of 2D worlds, rendering, and an integrated editor.**

[![C++](https://img.shields.io/badge/C%2B%2B-23%2F26-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![OpenGL](https://img.shields.io/badge/OpenGL-4.6-5586A4?style=for-the-badge&logo=opengl&logoColor=white)](https://www.opengl.org/)
[![CMake](https://img.shields.io/badge/CMake-4.3%2B-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)](LICENSE)
[![Status](https://img.shields.io/badge/status-experimental-orange?style=for-the-badge)]()
[![Focus](https://img.shields.io/badge/focus-2D%20engine-7B61FF?style=for-the-badge)]()

[✨ Explore the source](https://github.com/Peyman-Dev-Eng/Lucid_Drift/tree/master) · [🐛 Report a bug](https://github.com/Peyman-Dev-Eng/Lucid_Drift/issues) · [💡 Suggest an idea](https://github.com/Peyman-Dev-Eng/Lucid_Drift/issues)

*Still growing. Every system is another step toward a world of its own.* 🌌

</div>

---

## 📖 Overview

**Lucid Drift** is an experimental **2D game engine and editor written in modern C++ (C++23/C++26)**, using OpenGL for rendering and Dear ImGui for its editor interface.

The project brings together the parts of a small game-development workflow: rendering 2D geometry, browsing project files, editing source code, building a user game project, and loading its compiled module through an engine-facing API. The goal is not to imitate every feature of a mature commercial engine; it is to understand and build the underlying systems one piece at a time.

> [!WARNING]
> **Lucid Drift is a work in progress, not production-ready software.** APIs and workflows may change between commits, and some systems still need more testing—especially edge cases in geometry, camera transforms, input, and cross-platform support.

## ✨ Features at a glance

| System | What it brings | Status |
|:--|:--|:--:|
| 🎨 **OpenGL renderer** | A custom rendering path using OpenGL and GLSL shaders | Evolving |
| 🔷 **2D shape system** | Circle, line, and polygon workflows with thickness & joining | Evolving |
| 📐 **Polygon triangulation** | Triangulation for filled polygons, including concave shapes | In progress |
| 🔗 **Line joining algorithms** | Bevel, round, and miter joining for shape outlines | Evolving |
| 🖥️ **Editor interface** | Editor windows and controls built with Dear ImGui | Evolving |
| 🗂️ **Project Watch Tower** | Browse project folders and source files | Evolving |
| 📝 **Embedded code editor** | Source editing through ImGuiColorTextEdit | Integrated / evolving |
| 💡 **Code suggestions** | A custom keyword-based suggestion popup | In progress; not a full C++ language server |
| 🛠️ **Project compilation** | Build a user game project through CMake | Available in the current workflow |
| 🔌 **Engine API** | Call game lifecycle functions from a compiled module | Current Linux loading path |
| ⌨️ **Input system** | Engine-level keyboard/mouse input + key-target configuration | Evolving |
| 🎥 **Camera system** | Camera movement, zoom, and world-to-screen conversion | Evolving |
| 💾 **User project settings** | Read/write system for project settings and actor data | Experimental |
| 👁️ **Object management** | Object inspection / control window for scene actors | In progress |
| 🔍 **Convex / concave detection** | Shape classification helpers (`ShapeIsConcave`, etc.) | Evolving |

The status labels describe ongoing development, not a guarantee that every edge case is supported.

## 🧰 Technology stack

- **C++23 / C++26** — primary implementation language (CMake currently targets C++23)
- **CMake** — project configuration and build system
- **Ninja** — recommended generator for the commands below
- **OpenGL 4.6 Core Profile / GLSL 4.60** — graphics and shaders
- **GLFW** — window and OpenGL context management
- **GLM** — vector and matrix mathematics
- **Dear ImGui** — editor interface
- **ImGuiColorTextEdit** — embedded source editor
- **stb** — vendored image / utility support (where used)
- **GLAD** — OpenGL function loading

The repository's CMake configuration is the source of truth for required libraries and include paths. Dependencies can vary with the current branch and system setup.

---

## 🏗️ Project structure

The tree below highlights the main subsystems and how the code is organized. It is intentionally a subsystem-level view rather than a list of every source file; exact paths can change as the project evolves.

<details open>
<summary><b>📁 Explore the codebase</b></summary>

```text
Lucid_Drift/
├── CMakeLists.txt                 # Root CMake configuration
├── main.cpp                       # Application entry point
├── glad.c                         # GLAD implementation
├── glad/                          # OpenGL loader headers
├── LICENSE                        # MIT License
│
├── Main/
│   ├── CMakeLists.txt
│   ├── Assertion/                  # Assertion helpers
│   ├── EngineLibraries/
│   │   ├── Angle/                  # Angle utilities
│   │   ├── ShapeData/              # Shape-related data
│   │   ├── VecColor/               # Color utilities
│   │   └── VecPosition/            # 2D position/vector utilities
│   │
│   └── Engine/
│       ├── Actors/
│       │   ├── Line/               # Line shape
│       │   └── Shapes/
│       │       ├── MainShape/      # Shared shape foundation (convex/concave helpers)
│       │       ├── Circle/         # Circle shape
│       │       └── Polygon/        # Polygon shape
│       │
│       ├── Renderer/               # OpenGL rendering
│       ├── API/                    # Engine-facing game API
│       ├── Functions/              # Shared engine functions
│       ├── SubSystems/
│       │   ├── GraphicalUserInterfaceWindowHandler/  # GUI window handling logic
│       │   ├── PointHitTesting/    # Point / shape hit testing
│       │   ├── ProjectExplorer/    # Project Watch Tower / file browsing
│       │   ├── Transform/          # Transform-related logic
│       │   └── WR_SettingSystem/   # Window/render + user-project settings (read/write)
│       │
│       └── System/
│           ├── Camera/             # Camera movement, zoom, view matrix
│           ├── CodePathfinder/     # Code path / suggestion support
│           ├── Compilation/        # User-project build and module loading
│           ├── Core/               # Main engine coordination
│           ├── GUI/                # Dear ImGui windows and editor UI
│           ├── Input/              # Keyboard and mouse input
│           ├── Scene/              # Scene-related functionality
│           ├── Triangulation/      # Polygon triangulation
│           └── Window/             # Window/context management
│
└── ThirdParty/
    ├── imgui/                      # Dear ImGui sources
    └── ImGuiColorTextEdit/         # Embedded code-editor component
```

</details>

### 🧭 Where should I start?

| If you're interested in… | Start with… |
|:--|:--|
| How the project is built | `CMakeLists.txt` and `Main/CMakeLists.txt` |
| 2D geometry & line joining | `Actors/Shapes/`, `Actors/Line/`, and `Triangulation/` |
| Rendering | `Renderer/` |
| Editor windows | `System/GUI/` and `SubSystems/GraphicalUserInterfaceWindowHandler/` |
| Finding project files | `SubSystems/ProjectExplorer/` |
| Running user-written game code | `API/` and `System/Compilation/` |
| Input and key targets | `System/Input/` and `SubSystems/WR_SettingSystem/` |
| Camera & transforms | `System/Camera/` and `SubSystems/Transform/` |
| Project settings persistence | `SubSystems/WR_SettingSystem/` |

> [!TIP]
> For the exact source paths and build targets in your checkout, check the current `CMakeLists.txt` files. The structure shown here is a guide to the main responsibilities, not a promise that every folder name is identical across branches.

---

## 🔌 Game module API

The current game-module workflow connects user-written C++ code to the engine through three lifecycle functions:

- `BeginPlay()` — called when gameplay starts
- `Tick(float deltaTime)` — called during the game update loop
- `EndPlay()` — called when gameplay ends

### Example

```cpp
#include <EngineAPI.h>

extern "C" void BeginPlay()
{
    // Initialize game-specific state.
}

extern "C" void Tick(float deltaTime)
{
    // Update game logic using the elapsed frame time.
    (void)deltaTime;
}

extern "C" void EndPlay()
{
    // Release game-specific state.
}
```

### 📜 Important rules

| Rule | Why it matters |
|:--|:--|
| Use the exact names `BeginPlay`, `Tick`, and `EndPlay` | The loader looks up these entry points by name. |
| Keep `extern "C"` | Prevents C++ name mangling from changing the symbol names. |
| Use the exact `Tick(float)` signature | A different parameter type produces a different symbol/signature. |
| Build the game project as a shared library | The engine must be able to load the compiled module. |
| Match the expected name and output directory | The loader must find the generated library. |

On the current Linux loading path, the expected library name follows `lib<ProjectName>.so` (for example, `libTestProject.so`). The engine uses this shared library and the lifecycle entry points to connect user code to the runtime. Do not assume the same loading behavior on Windows until the platform-specific loader path has been verified in the branch you are using.

### 🎬 Lifecycle at a glance

```text
┌─────────────┐        ┌────────────────┐        ┌─────────────┐
│  BeginPlay  │ ─────▶ │ Tick(deltaTime)│ ─────▶ │   EndPlay   │
│   once      │        │   each frame   │        │   once      │
└─────────────┘        └───────┬────────┘        └─────────────┘
                               │
                               └── repeats while gameplay runs
```

---

## 🎨 Rendering & geometry

Lucid Drift's rendering foundation is built around a GLFW-created window and OpenGL context, with GLSL shaders handling the GPU-side rendering work.

- **Circles** are represented by polygonal geometry; the point count affects how smooth the outline appears. Thickness support is present and under refinement.
- **Lines** have their own shape and configuration workflow.
- **Polygons** use vertex data and triangulation for filled rendering.
- **Concave geometry** is detected via helpers such as `ShapeIsConcave` and remains an important area of active testing.
- **Line joining** supports bevel, round, and miter algorithms for outline corners.
- **World and screen coordinates** are intended to remain separate: shape data belongs to the world, while camera/viewport transforms determine how it is rendered.
- **Minimum window size** constraints are applied to keep the editor usable.

### 🔭 Coordinate flow

```text
Shape data in world space
          │
          ▼
 Camera / viewport transform
          │
          ▼
   Renderer vertex data
          │
          ▼
 OpenGL buffers + shaders
          │
          ▼
     Rendered frame
```

This is a conceptual view of the pipeline. Camera behavior, zoom, viewport conversion, and edge cases are still under active development.

---

## 🚀 Build the engine

These commands are a starting point for a Linux development environment. Confirm the dependencies against the CMake errors and the current build configuration.

### 1. Install the basic tools (Arch Linux)

```bash
sudo pacman -S --needed base-devel git cmake ninja glfw glm mesa libglvnd
```

This is not guaranteed to be an exhaustive dependency list for every revision. Install any additional development packages required by your checkout.

### 2. Clone the repository

```bash
git clone --branch master --single-branch https://github.com/Peyman-Dev-Eng/Lucid_Drift.git
cd Lucid_Drift
```

### 3. Configure

```bash
cmake -S . -B BUILD -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

### 4. Compile

```bash
cmake --build BUILD --parallel 14
```

Adjust the parallel job count to suit your machine. The application target is named `Lucid_Drift`; exact output paths are controlled by the active CMake configuration. Run the executable from the path reported by the build system.

> [!NOTE]
> The project requests an OpenGL 4.6 Core Profile context. Building successfully does not guarantee that the active graphics driver can create this context at runtime.

---

## 🚦 Development status

Lucid Drift is being built incrementally. Current areas of work include:

### 🌱 Actively evolving

- Improving circle, line, and polygon rendering (including thickness) and validating triangulation against difficult inputs.
- Refining camera movement, zoom, viewport handling, and world-to-screen conversion.
- Developing line-joining algorithms (bevel / round / miter) for clean outline corners.
- Improving the editor workflow for browsing, editing, compiling, and running game projects.
- Expanding keyboard/mouse input handling, key-target configuration, and persistence to user project settings.
- Building an object-management / inspection window for scene actors.
- Experimental read/write system for user-project settings and actor data.
- Making build and module-loading errors clearer and easier to diagnose.
- Convex / concave shape classification and related geometry helpers.

### 🧪 Not presented as finished

A complete physics engine, audio system, animation framework, asset pipeline, full scene serialization format, visual scripting system, and production-ready packaging workflow are **not claimed as finished features** by this README.

> ⚠️ Features may be incomplete, platform-specific, or subject to breaking changes. Check the source and recent commits to see the state of a particular subsystem.

---

## 🩺 Troubleshooting

| Problem | What to check |
|:--|:--|
| CMake cannot find a dependency | Read the first relevant CMake error; check installed development packages and include/library paths. |
| The compiler rejects a modern C++ feature | Verify the compiler version selected by CMake, not only the compiler installed on your system. |
| OpenGL context creation fails | Confirm the active driver exposes OpenGL 4.6 and supports the requested context. |
| A shape does not render correctly | Check the input points, generated vertices, triangulation output, thickness, and draw mode. |
| Line joining looks wrong | Verify the active joining algorithm (bevel / round / miter) and the geometry of the corner. |
| A game module builds but does not load | Check the exact shared-library filename, output directory, and exported entry-point names. |
| A lifecycle function cannot be found | Confirm the function name, `extern "C"`, and exact `Tick(float)` signature. |
| ImGui reports an unfinished frame | Trace the order of `NewFrame()`, `Render()`, and the backend drawing calls; do not add a second render call blindly. |
| Project settings are not saved / loaded | Inspect the experimental read-write path in `WR_SettingSystem` and the user project setting files. |

When reporting a bug, include your operating system, compiler and CMake versions, the build command, steps to reproduce, and the first relevant error or runtime log.

---

## 🤝 Contributing & feedback

Lucid Drift is a personal experimental project by **[Peyman-Dev-Eng](https://github.com/Peyman-Dev-Eng)**. Bug reports, focused fixes, and architectural suggestions are welcome. 🌱

When opening an issue, please include:

- 🖥️ Operating system and compiler version
- 🛠️ CMake version and build command
- 🎮 GPU / OpenGL information for graphics problems
- 🔁 Minimal steps to reproduce the issue
- 📋 Relevant build output or runtime logs

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

Third-party components (Dear ImGui, ImGuiColorTextEdit, stb, GLFW, GLM, etc.) retain their own licenses.

---

<div align="center">

### 🌊 Lucid Drift

*Build the systems. Shape the geometry. Create your world.*

**Still growing. Always drifting forward.**

⭐ If this project interests you, consider giving the repository a star!

</div>
