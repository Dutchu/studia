cmake_minimum_required(VERSION 3.28)
project(data_structures C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/simple_stack" "${PROJECT_SOURCE_DIR}/simple_stack/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/dynamic_stack" "${PROJECT_SOURCE_DIR}/dynamic_stack/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/calculator_stack" "${PROJECT_SOURCE_DIR}/calculator_stack/cmake-build-debug-wsl")