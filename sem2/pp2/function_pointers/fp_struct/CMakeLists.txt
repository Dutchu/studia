cmake_minimum_required(VERSION 3.16)
project(fp_struct C)

set(CMAKE_C_STANDARD 99)

add_executable(fp_struct
        main.c
        operations.c
        int_operations.c
        float_operations.c
        complex_operations.c)
