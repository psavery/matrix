project(matrix)

cmake_minimum_required(VERSION 2.6)

set(matrix_SRCS
    main.cpp
    matrix.cpp)

include_directories(${matrix_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable (matrix ${matrix_SRCS})
