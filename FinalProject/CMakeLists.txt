cmake_minimum_required(VERSION 3.10.3)
project(FinalProject)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-build-debug)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(FinalProject main.cpp)

target_link_libraries(FinalProject ${SDL2_LIBRARY}
        -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer)