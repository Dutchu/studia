cmake_minimum_required(VERSION 3.17)
project(files C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/1" "${PROJECT_SOURCE_DIR}/1/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/2" "${PROJECT_SOURCE_DIR}/2/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/3" "${PROJECT_SOURCE_DIR}/3/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/4" "${PROJECT_SOURCE_DIR}/4/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/5" "${PROJECT_SOURCE_DIR}/5/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/21" "${PROJECT_SOURCE_DIR}/21/cmake-build-debug")
