cmake_minimum_required(VERSION 3.17)
project(pojemnosci CXX)

set(CMAKE_CXX_STANDARD 17)

#define path to the utils
#set(UTILS_SOURCES
#        ${PROJECT_SOURCE_DIR}/../cycle_list_utils)

#define files to compile
set(PROJECT_SOURCES
        pojemnosci.cpp)
#        ${UTILS_SOURCES}/cycle_list_utils.c)

#add directory of utils
#include_directories("${UTILS_SOURCES}")

#create executable from sources
add_executable(pojemnosci ${PROJECT_SOURCES})
