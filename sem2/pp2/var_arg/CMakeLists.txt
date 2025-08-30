cmake_minimum_required(VERSION 3.28)
project(var_arg C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/sum" "${PROJECT_SOURCE_DIR}/sum/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/word_chain" "${PROJECT_SOURCE_DIR}/word_chain/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/array_chain" "${PROJECT_SOURCE_DIR}/array_chain/cmake-build-debug-wsl")