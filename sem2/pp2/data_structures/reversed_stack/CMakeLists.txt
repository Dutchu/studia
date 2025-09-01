cmake_minimum_required(VERSION 3.28)
project(reversed_stack C)

set(CMAKE_C_STANDARD 99)

add_executable(reversed_stack
        main.c
        stack.c
)
