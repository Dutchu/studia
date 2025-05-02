cmake_minimum_required(VERSION 3.17)
project(inttobytes C)

set(CMAKE_C_STANDARD 99)

#define path to the utils
set(UTILS_SOURCES
        ${PROJECT_SOURCE_DIR}/../utils)

#define files to compile
set(PROJECT_SOURCES
        main.c
        ${UTILS_SOURCES}/util.c)

#add directory of utils
include_directories("${UTILS_SOURCES}")

#create executable from sources
add_executable(inttobytes ${PROJECT_SOURCES})
