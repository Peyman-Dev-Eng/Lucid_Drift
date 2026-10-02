# Lucid Drift

**A lightweight, modern 2D graphics engine written in C++26 and OpenGL**

Lucid Drift is a 2D graphics engine / development tool focused on clean architecture, full control over low-level rendering, and built-in development utilities. The project is not fully complete yet, but it has reached a stable and usable state. Implementing a few remaining ideas will turn it into a complete engine.

---

## Current Features (Stable Core)

### Shape System (Actors)
- Base `Shape` class with full support for:
  - Vertices, per-vertex colors, thickness, fill mode
  - Directional movement (Up / Down / Left / Right)
  - Rotation
  - NDC coordinate transformation
  - Convex / concave detection
- Ready-to-use shapes:
  - `Circle` (with NDC radius support and dynamic rebuild)
  - `Polygon`
  - `Line` (converted to triangles for thick rendering)

### Rendering
- Custom OpenGL renderer (powered by GLAD)
- Support for filled and outline rendering modes
- Triangulation system for both convex and concave shapes
- VBO / VAO management and simple custom shaders

### Window & Input
- Window management with GLFW (fullscreen and resizable support)
- Keyboard and mouse input system
- Approximate framerate limiting (~60 FPS)

### Graphical User Interface
- Full **Dear ImGui** integration
- Built-in windows:
  - Project Watch Tower (project explorer)
  - Project Manager
  - Console (with `std::cout` redirection)
- Simple code editor support

### Development Tools
- **ProjectWatchTower**: Project management, folder structure creation, file writing, and automatic CMakeLists.txt generation for user projects
- **PointHitTesting**: Point-in-polygon collision detection
- Custom assertion system
- Core math libraries:
  - `VecPos2D` (positive coordinates only)
  - `VecCol` (RGBA with arithmetic operators)
  - `Angle`

---

## Project Architecture

```
Lucid_Drift/
├── Main/
│   ├── Assertion/                 # Custom assertion system
│   ├── Engine/
│   │   ├── Actors/                # Shapes (Shape, Circle, Polygon, Line)
│   │   ├── Renderer/              # OpenGL renderer
│   │   ├── System/
│   │   │   ├── Core/              # Engine core (main loop)
│   │   │   ├── Window/            # GLFW window management
│   │   │   ├── Input/             # Keyboard & mouse
│   │   │   ├── GUI/               # ImGui system
│   │   │   └── Triangulation/     # Convex / concave triangulation
│   │   ├── SubSystems/
│   │   │   ├── ProjectExplorer/   # ProjectWatchTower
│   │   │   ├── PointHitTesting/
│   │   │   └── GUI_lOGIC/
│   │   └── Functions/
│   └── EngineLibraries/           # VecPos2D, VecCol, Angle, ShapeData
├── glad/                          # GLAD (OpenGL loader)
├── ThirdParty/                    # imgui (must be added)
├── CMakeLists.txt
└── main.cpp
```

---

## Dependencies

- **C++26** (or at least C++23)
- **CMake** ≥ 4.3
- **GLFW3**
- **GLAD** (included in the repository)
- **Dear ImGui** (must be placed in `ThirdParty/imgui`)
- **fmt** (header-only)

---

## Building the Project

```bash
# Clone the repository
git clone https://github.com/Peyman-Dev-Eng/Lucid_Drift.git
cd Lucid_Drift

# Add ImGui (if not already present)
# git submodule add https://github.com/ocornut/imgui.git ThirdParty/imgui
# or copy it manually

mkdir build && cd build
cmake ..
cmake --build .
./Lucid_Drift
```

---

## Current Status

The project is in **Stable Preview** state:

- Core rendering, shapes, input, and GUI systems are stable
- Project management system (ProjectWatchTower) is functional
- Convex and concave triangulation is implemented
- Architecture is modular and ready for extension

### Remaining Ideas to Complete the Engine
- Simple physics system (advanced collision detection)
- Scene / Entity-Component system
- Texture and Sprite support
- Animation system
- Scene save / load
- Improved in-engine code editor
- Better support for complex concave shapes
- Camera and Viewport system
- Rendering optimizations (Batching, Instancing)

---

## Technical Notes

- `VecPos2D` only accepts positive values (non-positive coordinates are clamped to zero)
- The renderer works in NDC space and shapes are rebuilt when the window is resized
- The main loop is managed in `Core::EngineHandler` with an approximate 16 ms sleep
- All core libraries are built as static libraries

---

## Author

**Peyman-Dev-Eng**  
C++ developer passionate about game engine architecture and low-level graphics.

---

## License

This project does not have an official license yet. Currently free for personal use and learning.

---

> Built with love for modern C++ and OpenGL.  
> Still a long way from being complete, but the foundations are solid.
```