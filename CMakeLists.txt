cmake_minimum_required(VERSION 3.25)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)

add_executable(sudoku src/main.cpp)
target_include_directories(sudoku PRIVATE include)