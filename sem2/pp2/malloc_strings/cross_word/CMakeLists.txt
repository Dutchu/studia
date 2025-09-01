cmake_minimum_required(VERSION 3.17)
project(cross_word C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

#define files to compile
set(PROJECT_SOURCES main.c)

#create executable from sources
add_executable(cross_word ${PROJECT_SOURCES})