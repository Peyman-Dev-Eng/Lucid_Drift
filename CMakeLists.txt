cmake_minimum_required(VERSION 4.3)
project(Lucid_Drift)

set(CMAKE_CXX_STANDARD 26)
# Vector ###############################################################
add_library(VECTOR STATIC
        /home/Develepment/CLionProjects/Librarys/VECTOR/EmptySnakeBodyDataStructError.cpp
        /home/Develepment/CLionProjects/Librarys/VECTOR/InvalidInputError.cpp
        /home/Develepment/CLionProjects/Librarys/VECTOR/NotFoundElementError.cpp)

target_include_directories(VECTOR PUBLIC /home/Develepment/CLionProjects/Librarys/VECTOR)
########################################################################

# String ###############################################################
add_library(STRING STATIC
        /home/Develepment/CLionProjects/Librarys/STRING/Library/String/Error/IndexOutofRangeError/IndexOutofrange.cpp
        /home/Develepment/CLionProjects/Librarys/STRING/Library/String/MAIN/String.cpp)

target_include_directories(STRING PUBLIC /home/Develepment/CLionProjects/Librarys/STRING/Library/String/MAIN)
########################################################################

# Set ##################################################################
add_library(Set STATIC /home/Develepment/CLionProjects/Librarys/Set/Set.cpp)

target_include_directories(Set PUBLIC /home/Develepment/CLionProjects/Librarys/Set
)
########################################################################


# Queue ################################################################
add_library(QUEUE STATIC
        /home/Develepment/CLionProjects/Librarys/QUEUE/MAIN/Queue.cpp)

target_include_directories(QUEUE PUBLIC /home/Develepment/CLionProjects/Librarys/QUEUE/MAIN
)
########################################################################


# Map ##################################################################
add_library(MAP STATIC
        /home/Develepment/CLionProjects/Librarys/MapWithoutHashData/MAIN/Map.cpp
)
target_include_directories(MAP PUBLIC /home/Develepment/CLionProjects/Librarys/MapWithoutHashData/MAIN
)
########################################################################

# Hash Map #############################################################
add_library(HashMap STATIC
        /home/Develepment/CLionProjects/Librarys/MAP/HashMap.cpp
        /home/Develepment/CLionProjects/Librarys/MAP/NotFoundKeyError.cpp
        Main/Assertion/Assertions.cpp
        Main/Assertion/Assertions.h
)
target_include_directories(HashMap PUBLIC /home/Develepment/CLionProjects/Librarys/MAP
)
########################################################################

# Hash Set #############################################################
add_library(HashSet STATIC
        /home/Develepment/CLionProjects/Librarys/HashSet/Hash_Set.cpp
)
target_include_directories(HashSet PUBLIC /home/Develepment/CLionProjects/Librarys/HashSet
)
########################################################################


add_executable(Lucid_Drift main.cpp glad.c
        Main/Engine/System/Input/input.cpp
        Main/Engine/System/Input/input.h)



# Vector
target_link_libraries(Lucid_Drift PRIVATE VECTOR)

# String
target_link_libraries(Lucid_Drift PRIVATE STRING)

# Set
target_link_libraries(Lucid_Drift PRIVATE Set)

# Queue
target_link_libraries(Lucid_Drift PRIVATE QUEUE)

# Map
target_link_libraries(Lucid_Drift PRIVATE MAP)

# Hash Map
target_link_libraries(Lucid_Drift PRIVATE HashMap)

# Hash Set
target_link_libraries(Lucid_Drift PRIVATE HashSet)

target_link_libraries(HashSet PUBLIC STRING)
