cmake_minimum_required(VERSION 3.17)
project(allovarone C)

set(CMAKE_C_STANDARD 99)

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
add_executable(allovarone ${PROJECT_SOURCES})