add_library(Engine STATIC

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
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/imgui_demo.cpp
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp

        # Graphical User Interface System
        Engine/System/GUI/GUI.cpp
        Engine/System/GUI/GUI.h

        # Project Watch Tower System
        Engine/SubSystems/ProjectExplorer/ProjectWatchTower.cpp
        Engine/SubSystems/ProjectExplorer/ProjectWatchTower.h
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/glad/include
        Engine
)

target_link_libraries(Engine PUBLIC
        ASSERT
        VECPOS2D
        ANGLE
        VecColor
        glfw
        SHAPE_DATA
        PWT
)