###################################################################

## required version of cmake to build the project
cmake_minimum_required(VERSION 3.28)

## requirements of CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

###################################################################

## project name and version 
project(SudokuSolver VERSION 0.1)

## contains libraries for all classes used in the project
add_subdirectory(source)

add_executable(SudokuSolver SudokuSolver.cc)

target_link_libraries(SudokuSolver PUBLIC Grid )
target_link_libraries(SudokuSolver PUBLIC Cell )

###################################################################

enable_testing()

add_test(NAME Test1 COMMAND SudokuSolver Test1)
set( passRegex " Grid dimensions 9\n Grid number of squares 81")
set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION ${passRegex} )
