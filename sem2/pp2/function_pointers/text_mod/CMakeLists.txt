cmake_minimum_required(VERSION 3.16)
project(text_mod C)

set(CMAKE_C_STANDARD 99)

add_executable(text_mod
        main.c
        char_operations.c)
target_include_directories(text_mod PRIVATE ${CMAKE_CURRENT_LIST_DIR})

