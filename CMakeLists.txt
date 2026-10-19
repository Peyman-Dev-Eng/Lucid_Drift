if(WIN32)
    cmake_minimum_required(VERSION 3.24)
else()
    cmake_minimum_required(VERSION 4.3)
endif()

project(Lucid_Drift CXX C)

if(WIN32)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    # اجازه export خودکار کلاس‌ها/توابع از Engine.dll
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_compile_definitions(
        _CRT_SECURE_NO_WARNINGS
        NOMINMAX
        WIN32_LEAN_AND_MEAN
        _USE_MATH_DEFINES
    )

    add_compile_options(
        /W4
        /permissive-
        /Zc:__cplusplus
        /utf-8
        /EHsc
    )

    # DLL و EXE کنار هم در bin/
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

    foreach(cfg DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} "${CMAKE_BINARY_DIR}/bin")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${cfg} "${CMAKE_BINARY_DIR}/bin")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${cfg} "${CMAKE_BINARY_DIR}/lib")
    endforeach()
else()
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_subdirectory(Main)

add_executable(Lucid_Drift main.cpp)

target_link_libraries(Lucid_Drift PRIVATE Engine)

if(WIN32)
    target_link_libraries(Lucid_Drift PRIVATE opengl32)

    # کپی DLLهای وابسته کنار exe
    add_custom_command(TARGET Lucid_Drift POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Lucid_Drift>
            $<TARGET_FILE_DIR:Lucid_Drift>
        COMMAND_EXPAND_LISTS
    )
endif()