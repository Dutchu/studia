cmake_minimum_required(VERSION 3.28)
project(function_pointers C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/fp_param" "${PROJECT_SOURCE_DIR}/fp_param/cmake-build-debug-wsl")