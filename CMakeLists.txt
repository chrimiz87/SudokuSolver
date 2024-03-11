###################################################################

## required version of cmake to build the project
cmake_minimum_required(VERSION 3.28)

set( projectversion 0.1 )

## requirements of CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
##set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang") ## version 17

set(CMAKE_OSX_DEPLOYMENT_TARGET 14.0)

###################################################################

## project name and version 
project(SudokuSolver VERSION ${projectversion})

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

## project name and version
project(NineCellTester)
add_executable(NineCellTester NineCellTester.cc)

target_link_libraries(NineCellTester PUBLIC Cell)
target_link_libraries(NineCellTester PUBLIC NineCell)

###################################################################

enable_testing()

## define a function that helps generate tests
## arg is the argument passed to the program, as well as the name of the test
## result is the expected result of the test. If it is nothing, the default behaviour
## based on the return value (0==passed, 1==failed) is used
function( maketest arg executable result )
  add_test(NAME ${arg} COMMAND ${executable} ${arg} )

  if(NOT "${result}" STREQUAL "" )
    set_tests_properties( ${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result} )
  endif()
  
endfunction(maketest)

## SudokuTester
maketest(Test1 SudokuTester " Grid dimensions 9\n Grid number of squares 81")
maketest(Test2 SudokuTester " Warning in Grid::setCellValue. val 999 is not valid, must be from 1-9")
maketest(Test3 SudokuTester " Warning in Cell::setValue. tried to set value 3 but this cell is already solved with value 2")

## NineCellTester
## This code compares the output of NineCellTester to an existing output file.
## The test will fail if the output of NineCellTester is different to what it was in the past.
add_test(NAME NineCellTestRun COMMAND NineCellTester)
add_test(NAME NineCellTestCompare COMMAND ${CMAKE_COMMAND} -E compare_files
	      NineCellTester.txt NineCellTesterComparator.txt)
