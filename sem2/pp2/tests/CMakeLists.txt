cmake_minimum_required(VERSION 3.21)
project(tests C)

set(CMAKE_C_STANDARD 99)

#include_directories(structs)
#include_directories(structs/file_struct)
#include_directories(structs/hidden_message_II)
#include_directories(structs/struct_utils)
#
#add_executable(pp2
#        tests/translate/main.c
#        tests/utils/main.c
#        tests/utils/main.h)

add_subdirectory("${PROJECT_SOURCE_DIR}/translate" "${PROJECT_SOURCE_DIR}/translate/cmake-build-debug")