cmake_minimum_required(VERSION 4.3)

project(Lucid_Drift CXX C)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# Assertion
# ============================================================================

add_library(ASSERT STATIC
        Main/Assertion/Assertions.cpp
)

target_include_directories(ASSERT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Assertion
)


# ============================================================================
# Vector Position 2D
# ============================================================================

add_library(VECPOS2D STATIC
        Main/EngineLibraries/VecPosition/VecPos.cpp
)

target_include_directories(VECPOS2D PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/EngineLibraries/VecPosition
)

target_link_libraries(VECPOS2D PUBLIC
        ASSERT
)


# ============================================================================
# Angle
# ============================================================================

add_library(ANGLE STATIC
        Main/EngineLibraries/Angle/Angle.cpp
)

target_include_directories(ANGLE PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/EngineLibraries/Angle
)


# ============================================================================
# Vector Color
# ============================================================================

add_library(VecColor STATIC
        Main/EngineLibraries/VecColor/VecCol.cpp
)

target_include_directories(VecColor PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/EngineLibraries/VecColor
)


# ============================================================================
# Shape Data
# ============================================================================

add_library(SHAPE_DATA STATIC
        Main/EngineLibraries/ShapeData/ShapeData.cpp
)

target_include_directories(SHAPE_DATA PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/EngineLibraries/ShapeData
)

target_link_libraries(SHAPE_DATA PUBLIC
        VecColor VECPOS2D
)

# ============================================================================
# Project Watch Tower
# ===========================================================================

add_library(PWT STATIC
        Main/Engine/SubSystems/ProjectExplorer/ProjectWatchTower.cpp
)

target_include_directories(PWT PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Engine/SubSystems/ProjectExplorer
)

target_link_libraries(PWT PUBLIC
        ASSERT FUNCTIONS
)

# ============================================================================
# functions
# ============================================================================

add_library(FUNCTIONS STATIC
        Main/Engine/Functions/functions.cpp
)

target_include_directories(FUNCTIONS PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Engine/Functions
)

target_link_libraries(FUNCTIONS PUBLIC
        ASSERT PWT
)

# ============================================================================
# Dependencies
# ============================================================================

find_package(glfw3 REQUIRED)


# ============================================================================
# Engine
# ============================================================================

add_subdirectory(Main)


# ============================================================================
# Lucid Drift
# ============================================================================

add_executable(Lucid_Drift
        main.cpp
        glad.c
)

target_include_directories(Lucid_Drift PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

target_link_libraries(Lucid_Drift PRIVATE
        Engine
)

target_include_directories(Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui
        ${CMAKE_SOURCE_DIR}/ThirdParty/imgui/backends
        Engine
)