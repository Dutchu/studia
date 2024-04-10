cmake_minimum_required(VERSION 3.17)
project(1 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm ")

#define path to the utils
set(UTILS_SOURCES
        ${PROJECT_SOURCE_DIR}/../struct_utils)

#define files to compile
set(PROJECT_SOURCES
        main.c
        ${UTILS_SOURCES}/struct_utils.c)

#add directory of utils
include_directories("${UTILS_SOURCES}")

#create executable from sources
add_executable(1 ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} m)