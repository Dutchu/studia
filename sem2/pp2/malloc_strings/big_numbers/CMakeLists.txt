cmake_minimum_required(VERSION 3.17)
project(big_numbers C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

#define files to compile
set(PROJECT_SOURCES main.c)

#create executable from sources
add_executable(big_numbers ${PROJECT_SOURCES})