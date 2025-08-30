cmake_minimum_required(VERSION 3.28)
project(bit_op C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/compare" "${PROJECT_SOURCE_DIR}/compare/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/macros_bits" "${PROJECT_SOURCE_DIR}/macros_bits/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/macros_structs" "${PROJECT_SOURCE_DIR}/macros_structs/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/on_off_switch" "${PROJECT_SOURCE_DIR}/on_off_switch/cmake-build-debug-wsl")
