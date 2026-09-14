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

add_executable(Lucid_Drift main.cpp glad.c
        Main/Engine/System/Input/input.cpp
        Main/Engine/System/Input/input.h
)



# assert
target_link_libraries(Lucid_Drift PRIVATE ASSERT)
