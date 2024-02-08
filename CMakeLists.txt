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

target_link_libraries(SudokuSolver PUBLIC Cell )
target_link_libraries(SudokuSolver PUBLIC NineCell )
target_link_libraries(SudokuSolver PUBLIC Ternary )
target_link_libraries(SudokuSolver PUBLIC Grid )

###################################################################

## project name and version 
project(SudokuTester VERSION ${projectversion} )

add_executable(SudokuTester SudokuTester.cc)

target_link_libraries(SudokuTester PUBLIC Cell )
target_link_libraries(SudokuTester PUBLIC NineCell )
target_link_libraries(SudokuTester PUBLIC Ternary )
target_link_libraries(SudokuTester PUBLIC Grid )

###################################################################

enable_testing()

## define a function that helps generate tests
## arg is the argument passed to the program, as well as the name of the test
## result is the expected result of the test
function( maketest arg result )
  add_test(NAME ${arg} COMMAND SudokuTester ${arg} )
  set_tests_properties( ${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result} )
endfunction(maketest)

maketest(Test1 " Grid dimensions 9\n Grid number of squares 81")
maketest(Test2 " Warning in Grid::setCellValue. val 999 is not valid, must be from 1-9")
maketest(Test3 " Warning in Cell::setValue. tried to set value 3 but this cell is already solved with value 2")
