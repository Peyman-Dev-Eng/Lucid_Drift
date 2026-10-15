# Lucid Drift

**Lucid Drift** is an experimental C++ game-engine project focused on 2D rendering and an editor-driven workflow. It combines an OpenGL renderer with a Dear ImGui interface, scene and shape management, project compilation, and a small runtime API for loading game logic from a shared library.

The project is under active development. Interfaces and build workflows may change, and not every rendering feature should be considered production-ready.

## Contents

- [Highlights](#highlights)
- [Technology and requirements](#technology-and-requirements)
- [Build the engine](#build-the-engine)
  - [Linux](#linux)
  - [Windows](#windows)
- [Runtime API for game projects](#runtime-api-for-game-projects)
- [Architecture overview](#architecture-overview)
- [Troubleshooting](#troubleshooting)
- [Development status](#development-status)

## Highlights

- **C++26 codebase** built with CMake.
- **OpenGL renderer** using a GLFW-created window and GLSL shaders.
- **2D shape workflow** for working with polygon-based geometry and circle shapes. Geometry generation and rendering behavior are still evolving.
- **Editor interface** built with Dear ImGui for working with project and shape configuration tools.
- **Project management** for creating and exploring game-project files.
- **Build integration** for compiling a user project from the engine's project workflow.
- **Runtime game API** that loads a compiled shared library and resolves the `BeginPlay`, `Tick`, and `EndPlay` entry points.
- **Platform-specific input handling** for supported keyboard input paths on Linux and Windows.

## Technology and requirements

The exact dependency setup is defined by the repository's CMake configuration. Check `CMakeLists.txt` and any dependency directories before installing libraries separately.

The project currently expects the following environment:

- A C++ compiler with the C++26 support required by the source code.
- **CMake 4.3 or newer**, matching the version declared by the project.
- **OpenGL 4.6** support from the graphics driver, including GLSL 4.60 shaders.
- **GLFW** for window and input integration.
- **Dear ImGui** for the editor interface.
- **GLM** and any additional libraries referenced by the project's CMake files.
- **Ninja** is recommended for single-configuration builds, but another supported CMake generator can be used.

On Linux, make sure the OpenGL development files and a working graphics driver are installed. On Windows, use a compiler and generator combination that supports the C++ language features used by the project.

## Build the engine

### Linux

Clone the repository and configure a build directory:

```bash
git clone https://github.com/Peyman-Dev-Eng/Lucid_Drift.git
cd Lucid_Drift
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

Build the project:

```bash
cmake --build build --parallel
```

If configuration fails because a dependency cannot be found, install the development package for that dependency or update the relevant CMake path according to how the dependency is provided in the repository.

When the build completes, run the `Lucid_Drift` executable from the build output directory. With a single-configuration Ninja build, the expected path is commonly:

```bash
./build/Lucid_Drift
```

The exact output path can differ if the CMake configuration or generator places executables in a configuration-specific directory.

### Windows

Open a developer terminal for the compiler you intend to use, then run:

```powershell
git clone https://github.com/Peyman-Dev-Eng/Lucid_Drift.git
cd Lucid_Drift
cmake -S . -B build
cmake --build build --config Debug --parallel
```

Run `Lucid_Drift.exe` from the generated output directory. The path depends on the selected CMake generator and build configuration; for a multi-configuration generator, the executable is often inside `build/Debug/`.

> **Note:** These are the standard CMake configure/build steps. If the current branch changes its dependencies or build targets, follow the targets and requirements in that branch's `CMakeLists.txt`.

## Runtime API for game projects

Lucid Drift's project workflow is designed to build game logic as a shared library and load three C-linkage entry points. A game project should provide functions with the expected names and signatures; in particular, `Tick` receives a `float` argument.

A minimal example is:

```cpp
#include <EngineAPI.h>

#if defined(_WIN32)
    #define LUCID_DRIFT_GAME_EXPORT __declspec(dllexport)
#else
    #define LUCID_DRIFT_GAME_EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
    LUCID_DRIFT_GAME_EXPORT void BeginPlay()
    {
        // Called when game play begins.
    }

    LUCID_DRIFT_GAME_EXPORT void Tick(float deltaTime)
    {
        // Called during the game loop.
        (void)deltaTime;
    }

    LUCID_DRIFT_GAME_EXPORT void EndPlay()
    {
        // Called when game play ends.
    }
}
```

### Entry-point requirements

- Keep the names exactly as shown: `BeginPlay`, `Tick`, and `EndPlay`.
- Use `extern "C"` so the exported names are not C++-mangled.
- Match the expected signatures. In particular, implement `Tick(float deltaTime)`, not `Tick()`.
- Export the functions from the generated shared library, especially when building on Windows.
- Build the project as a shared library, not as a standalone executable, and ensure the library is written to the build location expected by the engine.

The Linux loader currently expects a library named `lib<ProjectName>.so` in the configured project build location. On Windows, make sure the generated DLL filename and exported symbols match the naming and loading rules in the current branch.

## Architecture overview

The engine is organized around a set of cooperating subsystems:

- **Core** — coordinates engine initialization and the main execution flow.
- **Window** — creates and manages the rendering window and related window events.
- **Renderer** — initializes OpenGL resources and submits shape geometry for rendering.
- **Scene** — stores and manages scene-level shape information.
- **GUI** — owns the Dear ImGui editor interface and its windows.
- **ProjectWatchTower** — handles project and file/folder management for the editor workflow.
- **Compile** — starts project builds and tracks their status.
- **EngineAPI** — loads a compiled game library and calls its lifecycle entry points.
- **Input** — provides platform-specific keyboard input handling.

These components are being developed together, so exact class APIs and internal responsibilities may evolve between commits.

## Troubleshooting

### CMake says that the build directory is not a CMake build tree

Configure the directory before building, or recreate it if it contains stale build files:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

Use the same build directory consistently for configuration and compilation.

### The window cannot create an OpenGL context

Check that the installed graphics driver exposes an OpenGL 4.6-capable context and that the required graphics libraries are available. A successful C++ build alone does not guarantee that the runtime driver supports the requested OpenGL version.

### The game library loads but the entry points are not found

Verify the library path and filename, export visibility, C linkage, and exact function signatures. A `Tick()` function does not match the expected `Tick(float)` entry point.

### The project does not build

Read the first relevant compiler or linker error rather than only the final build summary. Confirm that the active compiler supports the language features used by the project and that the dependencies configured in CMake are available.

## Development status

Lucid Drift is an actively developed project, not a stable engine release. Rendering, shape geometry, editor tooling, platform support, and the game-project workflow may be incomplete or change without backward compatibility. Circle and polygon geometry should be treated as work in progress until their behavior is verified on the target branch.

For useful bug reports, include the operating system, compiler and CMake versions, graphics driver/OpenGL version, the steps to reproduce the issue, and the relevant build or runtime log.
