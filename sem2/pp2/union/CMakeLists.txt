cmake_minimum_required(VERSION 3.21)
project(union C)

set(CMAKE_C_STANDARD 99)

add_subdirectory("${PROJECT_SOURCE_DIR}/inttobytes" "${PROJECT_SOURCE_DIR}/inttobytes/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/wordstoint" "${PROJECT_SOURCE_DIR}/wordstoint/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/bytetobits" "${PROJECT_SOURCE_DIR}/bytetobits/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/int4ways" "${PROJECT_SOURCE_DIR}/int4ways/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/bit_parity" "${PROJECT_SOURCE_DIR}/bit_parity/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/bitmap" "${PROJECT_SOURCE_DIR}/bitmap/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/figures" "${PROJECT_SOURCE_DIR}/figures/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/hidden_message" "${PROJECT_SOURCE_DIR}/hidden_message/cmake-build-debug")
#add_subdirectory("${PROJECT_SOURCE_DIR}/utils" "${PROJECT_SOURCE_DIR}/utils/cmake-build-debug")