cmake_minimum_required(VERSION 3.21)
project(structs C)

set(CMAKE_C_STANDARD 11)



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

add_subdirectory("${PROJECT_SOURCE_DIR}/point" "${PROJECT_SOURCE_DIR}/point/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/file_struct" "${PROJECT_SOURCE_DIR}/file_struct/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/hidden_message_II" "${PROJECT_SOURCE_DIR}/hidden_message_II/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/phone_book" "${PROJECT_SOURCE_DIR}/phone_book/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/phone_book_II" "${PROJECT_SOURCE_DIR}/phone_book_II/cmake-build-debug")
#add_subdirectory("${PROJECT_SOURCE_DIR}/test" "${PROJECT_SOURCE_DIR}/test/cmake-build-debug")
#add_subdirectory("${PROJECT_SOURCE_DIR}/struct_utils" "${PROJECT_SOURCE_DIR}/struct_utils/cmake-build-debug")