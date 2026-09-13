cmake_minimum_required(VERSION 4.3)
project(Lucid_Drift)

set(CMAKE_CXX_STANDARD 26)
# Vector ###############################################################
add_library(VECTOR STATIC
    Main/Library/VECTOR/EmptySnakeBodyDataStructError.cpp
    Main/Library/VECTOR/InvalidInputError.cpp
    Main/Library/VECTOR/NotFoundElementError.cpp)

target_include_directories(VECTOR PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/VECTOR)
########################################################################

# String ###############################################################
add_library(STRING STATIC
        Main/Library/STRING/Library/String/Error/IndexOutofRangeError/IndexOutofrange.cpp
        Main/Library/STRING/Library/String/MAIN/String.cpp)

target_include_directories(STRING PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/STRING/Library/String/MAIN)
########################################################################

# Set ##################################################################
add_library(Set STATIC Main/Library/Set/Set.cpp)

target_include_directories(Set PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/Set
)
########################################################################


# Queue ################################################################
add_library(QUEUE STATIC
        Main/Library/QUEUE/Library/QueueFiles/MAIN/Queue.cpp)

target_include_directories(QUEUE PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/QUEUE/Library/QueueFiles/MAIN
)
########################################################################


# Map ##################################################################
add_library(MAP STATIC
        Main/Library/MapWithoutHashData/MAIN/Map.cpp
)
target_include_directories(MAP PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/MapWithoutHashData/MAIN
)
########################################################################

# Hash Map #############################################################
add_library(HashMap STATIC
        Main/Library/MappingData/MAP/HashMap.cpp
        Main/Library/MappingData/MAP/NotFoundKeyError.cpp
)
target_include_directories(HashMap PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/MappingData/MAP
)
########################################################################

# Hash Set #############################################################
add_library(HashSet STATIC
        Main/Library/HashSet/Hash_Set.cpp
)
target_include_directories(HashSet PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Main/Library/HashSet
)
########################################################################


add_executable(Lucid_Drift main.cpp glad.c)



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

