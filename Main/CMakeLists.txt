add_library(Engine STATIC

        # System
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
        Engine/System/Window/Window.cpp
        Engine/System/Window/Window.h
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
)