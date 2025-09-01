cmake_minimum_required(VERSION 3.16)
project(moving_point C)

set(CMAKE_C_STANDARD 99)

add_executable(moving_point
        main.c
        board.c)
target_include_directories(moving_point PRIVATE ${CMAKE_CURRENT_LIST_DIR})

