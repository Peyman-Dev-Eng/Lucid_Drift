cmake_minimum_required(VERSION 4.3)

project(Lucid_Drift CXX C)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ============================================================================
# Engine
# ============================================================================

add_subdirectory(Main)


# ============================================================================
# Lucid Drift
# ============================================================================

add_executable(Lucid_Drift
        main.cpp
)

target_link_libraries(Lucid_Drift PRIVATE
        Engine
)