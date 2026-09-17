cmake_minimum_required(VERSION 4.3)
project(Lucid_Drift)

set(CMAKE_CXX_STANDARD 26)

# Assertion ############################################################
add_library(ASSERT STATIC
        Main/Assertion/Assertions.cpp
)
target_include_directories(ASSERT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Assertion
)
########################################################################

# Vector Position 2D ###################################################
add_library(VECPOS2D STATIC
        Main/EngineLibraries/VecPosition/VecPos.cpp
)
target_include_directories(VECPOS2D PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/EngineLibraries/VecPosition
)

########################################################################

add_executable(Lucid_Drift main.cpp glad.c
        Main/Engine/System/Input/input.cpp
        Main/Engine/System/Input/input.h
        Main/EngineLibraries/VecPosition/VecPos.cpp
        Main/EngineLibraries/VecPosition/VecPos.h
        Main/Engine/Actors/Shapes/MainShape/Shape.cpp
        Main/Engine/Actors/Shapes/MainShape/Shape.h
        Main/EngineLibraries/Angle/Angle.cpp
        Main/EngineLibraries/Angle/Angle.h
)

target_include_directories(Lucid_Drift PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)
find_package(glfw3 REQUIRED)

# assert
target_link_libraries(Lucid_Drift PRIVATE ASSERT glfw VECPOS2D)
target_link_libraries(VECPOS2D PUBLIC ASSERT)
