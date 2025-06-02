cmake_minimum_required(VERSION 3.17)
project(wordstoint C)

set(CMAKE_C_STANDARD 99)

set(UTILS_DIR
        ${CMAKE_SOURCE_DIR}/utils)

set(PROJECT_SOURCES
        main.c
        ${UTILS_DIR}/util.c)

add_executable(wordstoint ${PROJECT_SOURCES})
target_include_directories(wordstoint PRIVATE ${UTILS_DIR})