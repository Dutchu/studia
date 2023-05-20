cmake_minimum_required(VERSION 3.17)
project(types CXX)

set(CMAKE_CXX_STANDARD 17)

#define path to the utils
#set(UTILS_SOURCES
#        ${PROJECT_SOURCE_DIR}/../struct_utils)

#define files to compile
set(PROJECT_SOURCES
        types.cpp)
#        ${UTILS_SOURCES}/struct_utils.c)
#
##add directory of utils
#include_directories("${UTILS_SOURCES}")

#create executable from sources
add_executable(types ${PROJECT_SOURCES})
