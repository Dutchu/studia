cmake_minimum_required(VERSION 3.21)
project(malloc C)

set(CMAKE_C_STANDARD 11)

add_subdirectory("${PROJECT_SOURCE_DIR}/fill" "${PROJECT_SOURCE_DIR}/fill/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/allovarone" "${PROJECT_SOURCE_DIR}/allovarone/cmake-build-debug-wsl")