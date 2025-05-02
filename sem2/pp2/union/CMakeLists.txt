cmake_minimum_required(VERSION 3.21)
project(union C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/inttobytes" "${PROJECT_SOURCE_DIR}/inttobytes/cmake-build-debug")
#add_subdirectory("${PROJECT_SOURCE_DIR}/utils" "${PROJECT_SOURCE_DIR}/utils/cmake-build-debug")