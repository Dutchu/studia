cmake_minimum_required(VERSION 3.17)
project(overload CXX)

set(CMAKE_CXX_STANDARD 17)

#define path to the utils
#set(UTILS_SOURCES
#        ${PROJECT_SOURCE_DIR}/../struct_utils)

#define files to compile
set(PROJECT_SOURCES
        overload.cpp)
#        ${UTILS_SOURCES}/struct_utils.c)
#
##add directory of utils
#include_directories("${UTILS_SOURCES}")

#create executable from sources
add_executable(overload ${PROJECT_SOURCES})
