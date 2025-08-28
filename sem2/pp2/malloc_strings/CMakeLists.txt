cmake_minimum_required(VERSION 3.28)
project(malloc_strings C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/big_numbers" "${PROJECT_SOURCE_DIR}/big_numbers/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/ariadna" "${PROJECT_SOURCE_DIR}/ariadna/cmake-build-debug-wsl")