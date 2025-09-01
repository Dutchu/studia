cmake_minimum_required(VERSION 3.28)
project(text_chain C)

set(CMAKE_C_STANDARD 99)

add_executable(text_chain
        main.c
        concatenate.c
)
target_include_directories(text_chain PRIVATE ${CMAKE_CURRENT_LIST_DIR})

