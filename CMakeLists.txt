cmake_minimum_required(VERSION 3.30)
project(RayEngine)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

add_library(RayEngine STATIC
        src/EntryPoint.cpp
        include/EntryPoint.h
        include/core/Application.h
        src/core/Application.cpp
        include/core/Core.h
        include/core/Object.h
        include/core/Scene.h
        include/core/AssetsManager.h
        include/core/TimerManager.h
        src/core/Object.cpp
        src/core/TimerManager.cpp
        src/core/AssetsManager.cpp
        src/core/Scene.cpp
        include/ui/HUD.h
        src/ui/HUD.cpp
)

target_link_libraries(RayEngine PUBLIC raylib)

target_include_directories(RayEngine PUBLIC include)
