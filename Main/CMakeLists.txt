
set(LUCID_DRIFT_ROOT
        ${CMAKE_CURRENT_LIST_DIR}/..
)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(IMGUI_COLOR_TEXT_EDITOR_DIR
        "${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/ImGuiColorTextEdit"
)

# ============================================================================
# Assertion
# ============================================================================

add_library(ASSERT STATIC
        Assertion/Assertions.cpp
)

target_include_directories(ASSERT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Assertion
)


# ============================================================================
# Vector Position 2D
# ============================================================================

add_library(VECPOS2D STATIC
        EngineLibraries/VecPosition/VecPos.cpp
)

target_include_directories(VECPOS2D PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineLibraries/VecPosition
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
        ${LUCID_DRIFT_ROOT}/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/System/GUI
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends
)

target_link_libraries(VECPOS2D PUBLIC
        ASSERT VecColor ANGLE SHAPE_DATA PWT TRM COMP
)


# ============================================================================
# Angle
# ============================================================================

add_library(ANGLE STATIC
        EngineLibraries/Angle/Angle.cpp
)

target_include_directories(ANGLE PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineLibraries/Angle
)


# ============================================================================
# Vector Color
# ============================================================================

add_library(VecColor STATIC
        EngineLibraries/VecColor/VecCol.cpp
)

target_include_directories(VecColor PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineLibraries/VecColor
)


# ============================================================================
# Shape Data
# ============================================================================

add_library(SHAPE_DATA STATIC
        EngineLibraries/ShapeData/ShapeData.cpp
)

target_include_directories(SHAPE_DATA PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineLibraries/ShapeData
)

target_link_libraries(SHAPE_DATA PUBLIC
        VecColor VECPOS2D
)

# ============================================================================
# Project Watch Tower
# ===========================================================================

add_library(PWT STATIC
        Engine/SubSystems/ProjectExplorer/ProjectWatchTower.cpp
)

target_include_directories(PWT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/ProjectExplorer
)

target_link_libraries(PWT PUBLIC
        ASSERT FUNCTIONS
)

# ============================================================================
# functions
# ============================================================================

add_library(FUNCTIONS STATIC
        Engine/Functions/functions.cpp
)

target_include_directories(FUNCTIONS PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Functions
)

# ============================================================================
# GUI SYSTEM
# ============================================================================

add_library(GUI STATIC
        Engine/System/GUI/GUI.cpp
)

target_include_directories(GUI PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/System/GUI

        # GUI SubSystems
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/GraphicalUserInterfaceWindowHandler

        # Third-party libraries
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends
        ${LUCID_DRIFT_ROOT}/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/WR_SettingSystem
)

target_link_libraries(GUI PUBLIC
        ASSERT
        PWT
        VECPOS2D
        VecColor
        ANGLE
        SHAPE_DATA
        COMP
        CODE_PATHFINDER
)
# ============================================================================
# Transform System
# ============================================================================

add_library(TRM STATIC
        Engine/SubSystems/Transform/Transform.cpp
)

target_include_directories(TRM PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/Transform
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
        ${LUCID_DRIFT_ROOT}/glad/include
)

target_link_libraries(TRM PUBLIC
        VECPOS2D
        VecColor
        SHAPE_DATA
        ASSERT
        FUNCTIONS
        GUI
)

# ============================================================================
# Egnine API
# ============================================================================

add_library(ENG_API STATIC
        Engine/API/EngineAPI.cpp
)

target_include_directories(ENG_API PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/API
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/WR_SettingSystem
)

target_link_libraries(ENG_API PUBLIC
        PWT FUNCTIONS GUI
)

# ============================================================================
# Compile System
# ============================================================================

add_library(COMP STATIC
        Engine/System/Compilation/Compile.cpp
)

target_include_directories(COMP PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/System/Compilation
)

target_link_libraries(COMP PUBLIC
        PWT GUI
)

# ============================================================================
# Write and Read Engine Setting System
# ============================================================================

add_library(WRSS STATIC
        Engine/SubSystems/WR_SettingSystem/WR_SettingSystem.cpp
)

target_include_directories(WRSS PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/WR_SettingSystem
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineLibraries/VecPosition
        ${CMAKE_CURRENT_SOURCE_DIR}/EngineLibraries/VecColor
)

target_link_libraries(WRSS PUBLIC PWT ANGLE SHAPE_DATA )

# ============================================================================
# Code Pathfinder system
# ============================================================================

add_library(CODE_PATHFINDER STATIC
        Engine/System/CodePathfinder/CodePathfinder.cpp
)

target_include_directories(CODE_PATHFINDER PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/System/CodePathfinder
)
# ============================================================================
# END
# ============================================================================

add_library(__GUIWH__ STATIC
        Engine/SubSystems/GraphicalUserInterfaceWindowHandler/GraphicalUserInterfaceWindowHandler.cpp
)

target_include_directories(__GUIWH__ PUBLIC
        Engine/SubSystems/GraphicalUserInterfaceWindowHandler
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/WR_SettingSystem
)

target_link_libraries(__GUIWH__ PUBLIC GUI)

# ============================================================================
# END
# ============================================================================


if (WIN32)
    include(FetchContent)

    # --- GLFW ---
    find_package(glfw3 QUIET)
    if (NOT glfw3_FOUND)
        FetchContent_Declare(glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG 3.4
        )
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(glfw)
    endif ()

    # --- fmt ---
    find_package(fmt QUIET)
    if (NOT fmt_FOUND)
        FetchContent_Declare(fmt
                GIT_REPOSITORY https://github.com/fmtlib/fmt.git
                GIT_TAG 11.0.2
        )
        FetchContent_MakeAvailable(fmt)
    endif ()

    # --- nlohmann_json ---
    find_package(nlohmann_json QUIET)
    if (NOT nlohmann_json_FOUND)
        FetchContent_Declare(nlohmann_json
                GIT_REPOSITORY https://github.com/nlohmann/json.git
                GIT_TAG v3.11.3
        )
        FetchContent_MakeAvailable(nlohmann_json)
    endif ()
else ()
    find_package(glfw3 REQUIRED)
    find_package(fmt REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED)
endif ()

add_library(Engine SHARED

        # glad - OpenGL
        ${LUCID_DRIFT_ROOT}/glad.c

        # System - input
        Engine/System/Input/input.cpp
        Engine/System/Input/input.h

        # Actors - Main Shape
        Engine/Actors/Shapes/MainShape/Shape.cpp
        Engine/Actors/Shapes/MainShape/Shape.h

        # Actors - Circle
        Engine/Actors/Shapes/Circle/CircleShape.cpp
        Engine/Actors/Shapes/Circle/CircleShape.h

        # Actors - Polygon
        Engine/Actors/Shapes/Polygon/Polygon.cpp
        Engine/Actors/Shapes/Polygon/Polygon.h

        # Actors - Line
        Engine/Actors/Line/Line.cpp
        Engine/Actors/Line/Line.h

        # System - Window
        Engine/System/Window/Window.cpp
        Engine/System/Window/Window.h

        # Renderer
        Engine/Renderer/Renderer.cpp
        Engine/Renderer/Renderer.h

        # Triangulation
        Engine/System/Triangulation/Triangulation.cpp
        Engine/System/Triangulation/Triangulation.h

        # Point Hit Testing
        Engine/SubSystems/PointHitTesting/PointHitTesting.cpp
        Engine/SubSystems/PointHitTesting/PointHitTesting.h

        # Dear ImGui
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/imgui.cpp
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/imgui_draw.cpp
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/imgui_tables.cpp
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/imgui_widgets.cpp
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/imgui_demo.cpp
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends/imgui_impl_glfw.cpp
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp

        # Graphical User Interface System
        Engine/System/GUI/GUI.cpp
        Engine/System/GUI/GUI.h

        # Engine Core - System
        Engine/System/Core/Core.cpp
        Engine/System/Core/Core.h

        # Scene - System
        Engine/System/Scene/Scene.cpp
        Engine/System/Scene/Scene.h

        # Engine API
        Engine/API/EngineAPI.h
        Engine/API/EngineAPI.cpp

        # Write and Read Setting System
        Engine/SubSystems/WR_SettingSystem/WR_SettingSystem.cpp
        Engine/SubSystems/WR_SettingSystem/WR_SettingSystem.h

        # cmera - system
        Engine/System/Camera/Camera.cpp
        Engine/System/Camera/Camera.h
)

target_include_directories(Engine PUBLIC
        ${LUCID_DRIFT_ROOT}/glad/include
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends
        ${CMAKE_CURRENT_LIST_DIR}/Engine
        ${CMAKE_CURRENT_LIST_DIR}/Engine/API
)

target_link_libraries(Engine PUBLIC
        ASSERT
        VECPOS2D
        ANGLE
        VecColor
        glfw
        SHAPE_DATA
        PWT
        FUNCTIONS
        GUI
        TRM
        COMP
        ENG_API
        CODE_PATHFINDER
        __GUIWH__
        WRSS
)

if (WIN32)
    target_link_libraries(Engine PUBLIC opengl32)
endif ()

target_include_directories(GUI PUBLIC
        "${IMGUI_COLOR_TEXT_EDITOR_DIR}"
)

target_sources(GUI PRIVATE
        "${IMGUI_COLOR_TEXT_EDITOR_DIR}/TextEditor.cpp"
)

target_link_libraries(GUI PRIVATE
        nlohmann_json::nlohmann_json
)
target_link_libraries(Engine
        PRIVATE
        nlohmann_json::nlohmann_json
)