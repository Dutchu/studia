cmake_minimum_required(VERSION 3.17)
project(mirror_image C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(PROJECT_SOURCES main.c)

add_executable(mirror_image image_utils.c ${PROJECT_SOURCES})

