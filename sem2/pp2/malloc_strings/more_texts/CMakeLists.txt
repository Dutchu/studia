cmake_minimum_required(VERSION 3.17)
project(more_texts C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(PROJECT_SOURCES main.c)

add_executable(more_texts ${PROJECT_SOURCES})

