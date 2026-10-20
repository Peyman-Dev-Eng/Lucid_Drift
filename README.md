<div align="center">
    
# 🌊 Lucid Drift

**Lucid Drift — A free flow of imagination, with the clarity to create your own world.**

**A lucid exploration of modern C++ game engine design.**

[![C++](https://img.shields.io/badge/C%2B%2B-26-blue?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![OpenGL](https://img.shields.io/badge/OpenGL-4.6-5586A4?style=for-the-badge&logo=opengl&logoColor=white)](https://www.opengl.org/)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey?style=for-the-badge)]()
[![Status](https://img.shields.io/badge/status-experimental-orange?style=for-the-badge)]()

*Still growing. Already stable enough to drift.* 🌊

</div>

---

## 📖 Overview

**Lucid Drift** is an experimental 2D game engine written in modern C++ with OpenGL and Dear ImGui.
It's designed as a **learning / research project** for exploring modern engine architecture — a plugin-based runtime, a custom renderer, and an integrated editor.

> ⚠️ This is **not production-ready software**. Expect breaking changes between commits.

---

## ✨ Features

- 🎮 **Plugin-based game runtime** — games are compiled as shared libraries and hot-loaded
- 🎨 **Custom OpenGL renderer** with GLSL shaders and batched draw calls
- 🔷 **2D Shape system** — Circle, Polygon (convex & concave), and Line
- 📐 **Polygon triangulation** — supports concave geometry
- 🖥️ **Dear ImGui editor** with dockable windows
- 📂 **Project explorer** & code buffer
- 🛠️ **In-editor compilation pipeline**
- ⌨️ **Basic input handling**

---

## 🖼️ Project Structure

<details>
<summary><b>📁 Click to expand</b></summary>

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

</details>

---

## 🔌 Game Plugin API

Writing gameplay logic in Lucid Drift needs only **three functions**.
Compile your code → the engine loads it → the game begins. 🚀

```cpp
#if defined(_WIN32)
    #define LUCID_DRIFT_GAME_EXPORT __declspec(dllexport)
#else
    #define LUCID_DRIFT_GAME_EXPORT __attribute__((visibility("default")))
#endif

extern "C" {

LUCID_DRIFT_GAME_EXPORT void BeginPlay() {
    // Called once when gameplay starts
}

LUCID_DRIFT_GAME_EXPORT void Tick(float deltaTime) {
    // Called every frame
    (void)deltaTime;
}

LUCID_DRIFT_GAME_EXPORT void EndPlay() {
    // Called when gameplay ends
}

}
```

### 📜 The Golden Rules

| ✅ | Rule |
|:--:|:-----|
| 🔤 | Function names must be **exactly** `BeginPlay`, `Tick`, `EndPlay` |
| 🌐 | Must use `extern "C"` (no name mangling) |
| ⏱️ | `Tick` **must** take a `float` parameter (delta time) |
| 📦 | Build as a **shared library** → `lib<ProjectName>.so` (Linux) / `<ProjectName>.dll` (Windows) |
| 🪟 | On Windows, export symbols with `__declspec(dllexport)` |
| 🔗 | Engine loads the library after compilation and calls the lifecycle through the **EngineAPI** subsystem |

### 🎬 Lifecycle

```text
┌─────────────┐     ┌──────────────┐     ┌─────────────┐
│  BeginPlay  │ ──▶ │     Tick     │ ──▶ │   EndPlay   │
│   (once)    │     │ (every frame)│     │   (once)    │
└─────────────┘     └──────┬───────┘     └─────────────┘
                           │
                    ↻ loops until quit
```

---

## 🧩 Key Subsystems

### 🔷 Shape System

| Shape | Status | Notes |
|:------|:------:|:------|
| **Base Shape** | ✅ | Foundation class for all shapes |
| **CircleShape** | ✅ | Smooth, fast, trivial triangulation |
| **Polygon** | ✅ | Supports **convex & concave** via Triangulation |
| **Line** | ✅ | Lightweight primitive for outlines & grids |

### 🎨 Renderer

- 🖌️ Custom **GLSL shaders**
- 📦 **Batched rendering** — shapes & lines share a single VBO
- 🎭 Supports **filled** and **outline** modes
- 🔄 Auto-rebuilds geometry when shapes change

### 🖥️ Editor / GUI

- 🪟 Multiple **dockable windows**
- 📂 **Project explorer** integration
- 📝 **Code buffer** for viewing & editing
- 📺 **Console-like** output redirection

### ⚙️ Project & Compilation Pipeline

```text
  ┌──────────────┐      ┌───────────────┐      ┌──────────────┐
  │ Create/Open  │ ───▶ │  Write Code   │ ───▶ │  Compile →   │
  │   Project    │      │  in Editor    │      │  .so / .dll  │
  └──────────────┘      └───────────────┘      └──────┬───────┘
                                                       │
                                                       ▼
  ┌──────────────┐      ┌───────────────┐      ┌──────────────┐
  │   EndPlay    │ ◀─── │  Tick Loop    │ ◀─── │  BeginPlay   │
  └──────────────┘      └───────────────┘      └──────────────┘
```

---

## 🚦 Development Status & Limitations

> Lucid Drift has reached a **stable foundation** — but it is **not a finished engine**.
> Treat it as a **research / learning / experimental** project.

### ✅ What's Stable

- 🏗️ Core architecture & main loop
- 🪟 Window + OpenGL context creation
- 🔷 Basic 2D shape rendering (Circle + Polygon)
- 📐 Polygon triangulation
- 🖥️ Dear ImGui editor integration
- 📁 Project file/folder management
- 🛠️ Compilation triggering & shared-library loading
- 🔌 Runtime lifecycle API (`BeginPlay` / `Tick` / `EndPlay`)
- ⌨️ Basic input handling

### 🧪 What's Incomplete / Experimental

- ✏️ Full shape editing tools & property panels
- 🧭 Advanced transform system
- 💥 Physics / collision *(beyond basic point hit testing)*
- 🎥 Camera system
- 📦 Asset pipeline *(textures, fonts, audio, …)*
- 💾 Serialization of scenes / projects
- 🌍 Cross-platform polish & packaging
- 📚 Documentation of all internal APIs
- ⚡ Performance optimizations & batching improvements
- 🛡️ Complete error handling & recovery paths

> ⚠️ **Expect breaking changes** in internal APIs between commits.

---

## 🩺 Troubleshooting

| 🚨 Problem | 💡 Possible Solution |
|:-----------|:---------------------|
| CMake cannot find GLFW / fmt | Install dev packages or set `CMAKE_PREFIX_PATH` |
| OpenGL context creation fails | Ensure your GPU driver supports **OpenGL 4.6** |
| ImGui not found | Place Dear ImGui sources in `ThirdParty/imgui` |
| Library loads but entry points missing | Check `extern "C"`, exact signatures, and export visibility |
| Build fails with C++26 features | Use a recent compiler (**GCC 14+**, **Clang 18+**, latest **MSVC**) |
| Shapes not rendering | Check they're added to the Renderer and triangulation succeeded |

---

## 🤝 Contributing & Feedback

This is primarily a personal experimental project by **[Peyman-Dev-Eng](https://github.com/Peyman-Dev-Eng)**.
Bug reports, architectural suggestions, and pull requests are **welcome**! 🌱

When reporting an issue, please include:

- 🖥️ Operating system
- 🛠️ Compiler + CMake versions
- 🎮 Graphics driver / OpenGL version
- 🔁 Steps to reproduce
- 📋 Relevant build or runtime logs

---

<div align="center">

### 🌊 Lucid Drift

*A lucid exploration of modern C++ game engine design.*

**Still growing. Already stable enough to drift.**

⭐ If you find this project interesting, consider giving it a star!

</div>
