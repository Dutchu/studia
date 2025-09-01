cmake_minimum_required(VERSION 3.28)
project(my_io C)

set(CMAKE_C_STANDARD 99)

add_executable(my_io main.c my_io.c)
