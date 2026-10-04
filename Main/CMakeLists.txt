
set(LUCID_DRIFT_ROOT
        ${CMAKE_CURRENT_LIST_DIR}/..
)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


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
)

target_link_libraries(VECPOS2D PUBLIC
        ASSERT
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

target_link_libraries(FUNCTIONS PUBLIC)

# ============================================================================
# GUI LOGIC
# ============================================================================

add_library(GL STATIC
        Engine/SubSystems/GUI_lOGIC/GuiLogic.cpp
)

target_include_directories(GL PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/GUI_lOGIC
)

target_link_libraries(GL PUBLIC
        GUI
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
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/SubSystems/GUI_lOGIC
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends
        ${LUCID_DRIFT_ROOT}/glad/include
)

target_link_libraries(GUI PUBLIC
        ASSERT
        PWT
        VECPOS2D
        VecColor
        ANGLE
        SHAPE_DATA
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
        ${PROJECT_SOURCE_DIR}/glad/include
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
# END
# ============================================================================


find_package(glfw3 REQUIRED)

find_package(fmt REQUIRED)

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

        # Compilation - System
        Engine/System/Compilation/Compile.cpp
        Engine/System/Compilation/Compile.h
)

target_include_directories(Engine PUBLIC
        ${LUCID_DRIFT_ROOT}/glad/include
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui
        ${LUCID_DRIFT_ROOT}/ThirdParty/imgui/backends
        ${CMAKE_CURRENT_LIST_DIR}/Engine
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
        GL
        GUI
        TRM
)
