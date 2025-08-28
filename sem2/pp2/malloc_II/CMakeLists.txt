
cmake_minimum_required(VERSION 3.28)
project(malloc_II C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/multiplication" "${PROJECT_SOURCE_DIR}/multiplication/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/array_2d" "${PROJECT_SOURCE_DIR}/array_2d/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/array_2d_II" "${PROJECT_SOURCE_DIR}/array_2d_II/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/matrix" "${PROJECT_SOURCE_DIR}/matrix/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/matrix_II" "${PROJECT_SOURCE_DIR}/matrix_II/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/matrix_ops" "${PROJECT_SOURCE_DIR}/matrix_ops/cmake-build-debug-wsl")
add_subdirectory("${PROJECT_SOURCE_DIR}/img_in_img" "${PROJECT_SOURCE_DIR}/img_in_img/cmake-build-debug-wsl")