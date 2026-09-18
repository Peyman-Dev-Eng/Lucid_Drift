add_library(Engine STATIC

        # System
        System/Input/input.cpp
        System/Input/input.h

        # Actors - Main Shape
        Actors/Shapes/MainShape/Shape.cpp
        Actors/Shapes/MainShape/Shape.h

        # Actors - Circle
        Actors/Shapes/Circle/CircleShape.cpp
        Actors/Shapes/Circle/CircleShape.h

        # Actors - Polygon
        Actors/Shapes/Polygon/Polygon.cpp
        Actors/Shapes/Polygon/Polygon.h

        # Actors - Line
        Actors/Line/Line.cpp
        Actors/Line/Line.h
        System/Window/Window.cpp
        System/Window/Window.h
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Engine PUBLIC
        ASSERT
        VECPOS2D
        ANGLE
        VecColor
        glfw
)