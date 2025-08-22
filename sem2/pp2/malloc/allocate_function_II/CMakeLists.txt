cmake_minimum_required(VERSION 3.17)
project(allocate_function_II C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

#define path to the utils
set(UTILS_SOURCES
        ${CMAKE_SOURCE_DIR}/utils)

#define files to compile
set(PROJECT_SOURCES
        main.c
        ${UTILS_SOURCES}/utils.c)

#add directory of utils
include_directories("${UTILS_SOURCES}")

#create executable from sources
add_executable(allocate_function_II ${PROJECT_SOURCES})