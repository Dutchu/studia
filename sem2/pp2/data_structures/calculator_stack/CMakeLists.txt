cmake_minimum_required(VERSION 3.28)
project(calculator_stack C)

set(CMAKE_C_STANDARD 99)

add_executable(calculator_stack
        main.c
        stack.c
)
