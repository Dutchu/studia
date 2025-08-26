
cmake_minimum_required(VERSION 3.28)
project(malloc_II C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/multiplication" "${PROJECT_SOURCE_DIR}/multiplication/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/array_2d" "${PROJECT_SOURCE_DIR}/array_2d/cmake-build-debug-wsl")