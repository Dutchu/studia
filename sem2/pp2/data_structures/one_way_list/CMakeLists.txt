cmake_minimum_required(VERSION 3.28)

add_executable(one_way_list
        main.c
        linked_list.c
)

target_include_directories(one_way_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

