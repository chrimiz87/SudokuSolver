###################################################################

## required version of cmake to build the project
cmake_minimum_required(VERSION 3.28)

set( projectversion 0.1 )

## requirements of CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

###################################################################

## project name and version 
project(SudokuSolver VERSION ${projectversion} )

## contains libraries for all classes used in the project
add_subdirectory(source)

add_executable(SudokuSolver SudokuSolver.cc)

target_link_libraries(SudokuSolver PUBLIC Grid )
target_link_libraries(SudokuSolver PUBLIC Cell )

###################################################################

## project name and version 
project(SudokuTester VERSION ${projectversion} )

add_executable(SudokuTester SudokuTester.cc)

target_link_libraries(SudokuTester PUBLIC Grid )
target_link_libraries(SudokuTester PUBLIC Cell )

###################################################################

enable_testing()

add_test(NAME Test1 COMMAND SudokuTester Test1)
set( passRegex1 " Grid dimensions 9\n Grid number of squares 81")
set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION ${passRegex1} )

add_test(NAME Test2 COMMAND SudokuTester Test2)
set( passRegex2 " Warning in Grid::setCellValue. val 999 is not valid, must be from 1-9")
set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION ${passRegex2} )

add_test(NAME Test3 COMMAND SudokuTester Test3)
set( passRegex3 " Warning Cell::setValue. tried to set value 3 but this cell is already solved with value 2")
set_tests_properties(Test3 PROPERTIES PASS_REGULAR_EXPRESSION ${passRegex3} )
