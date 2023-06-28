cmake_minimum_required(VERSION 3.25)
project(sudoku)
set(CMAKE_CXX_STANDARD 17)


include_directories(./include)
link_directories(./lib)
add_executable(sudoku src/main.cpp)
add_executable(sudoku_test test/test.cpp)
target_link_libraries(sudoku_test libgtest.a libgtest_main.a)
