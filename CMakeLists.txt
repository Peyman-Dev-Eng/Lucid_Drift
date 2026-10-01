cmake_minimum_required(VERSION 4.3)

project(Lucid_Drift CXX C)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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