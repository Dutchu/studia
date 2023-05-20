cmake_minimum_required(VERSION 3.21)
project(fz CXX)

set(CMAKE_CXX_STANDARD 17)

#include_directories(structs)
#include_directories(structs/file_struct)
#include_directories(structs/hidden_message_II)
#include_directories(structs/struct_utils)
#
#add_executable(pp2
#        structs/file_struct/main.c
#        structs/hidden_message_II/main.c
#        structs/struct_utils/main.c
#        structs/struct_utils/main.h)

add_subdirectory("${PROJECT_SOURCE_DIR}/pojemnosci" "${PROJECT_SOURCE_DIR}/pojemnosci/cmake-build-debug")


#add_subdirectory("${PROJECT_SOURCE_DIR}/test" "${PROJECT_SOURCE_DIR}/test/cmake-build-debug")
#add_subdirectory("${PROJECT_SOURCE_DIR}/struct_utils" "${PROJECT_SOURCE_DIR}/struct_utils/cmake-build-debug")