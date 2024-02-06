## required version of cmake to build the project
cmake_minimum_required(VERSION 3.28)

## project name and version 
project(SudokuSolver VERSION 0.1)

## requirements of CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## contains libraries for all classes used in the project
add_subdirectory(source)

add_executable(SudokuSolver SudokuSolver.cc)

target_link_libraries(SudokuSolver PUBLIC Grid )
target_link_libraries(SudokuSolver PUBLIC Cell )



