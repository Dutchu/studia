cmake_minimum_required(VERSION 3.21)
project(malloc C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/fill" "${PROJECT_SOURCE_DIR}/fill/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/allovarone" "${PROJECT_SOURCE_DIR}/allovarone/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/cyclic_buffer" "${PROJECT_SOURCE_DIR}/cyclic_buffer/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/vector" "${PROJECT_SOURCE_DIR}/vector/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/safe_array" "${PROJECT_SOURCE_DIR}/safe_array/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/safe_array_II" "${PROJECT_SOURCE_DIR}/safe_array_II/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/allocate_function" "${PROJECT_SOURCE_DIR}/allocate_function/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/allocate_function_II" "${PROJECT_SOURCE_DIR}/allocate_function_II/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/copy_print" "${PROJECT_SOURCE_DIR}/copy_print/cmake-build-debug-wsl")