cmake_minimum_required(VERSION 3.17)
project(student_record C)

set(CMAKE_C_STANDARD 99)

set(UTILS_SOURCES
        ${CMAKE_SOURCE_DIR}/struct_utils)

set(PROJECT_SOURCES
        main.c
        ${UTILS_SOURCES}/struct_utils.c)

include_directories("${UTILS_SOURCES}")

add_executable(student_record ${PROJECT_SOURCES})
target_include_directories(student_record PRIVATE ${UTILS_SOURCES})