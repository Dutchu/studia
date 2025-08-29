cmake_minimum_required(VERSION 3.28)
project(var_arg C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/sum" "${PROJECT_SOURCE_DIR}/sum/cmake-build-debug-wsl")
