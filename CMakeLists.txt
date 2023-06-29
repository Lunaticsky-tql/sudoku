cmake_minimum_required(VERSION 3.25)
project(sudoku)
set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
# gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
# gather files for testing (do not include src/main.cpp)
file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_executable(sudoku ${SOURCES})
add_executable(sudoku_test test/test.cpp ${TEST_SOURCES})
target_link_libraries(sudoku_test libgtest.a libgtest_main.a)
