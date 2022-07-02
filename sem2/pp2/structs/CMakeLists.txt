cmake_minimum_required(VERSION 3.21)
project(structs C)

set(CMAKE_C_STANDARD 11)

#include_directories(structs)
#include_directories(structs/18)
#include_directories(structs/20)
#include_directories(structs/utils)
#
#add_executable(pp2
#        structs/18/main.c
#        structs/20/main.c
#        structs/utils/main.c
#        structs/utils/main.h)

add_subdirectory("${PROJECT_SOURCE_DIR}/18" "${PROJECT_SOURCE_DIR}/18/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/20" "${PROJECT_SOURCE_DIR}/20/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/utils" "${PROJECT_SOURCE_DIR}/utils/cmake-build-debug")