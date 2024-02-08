#include <iostream>

#include "Grid.hh"

int main(int argc, char** argv){

  if(argc>1){
    // testing mode.

    // testing basic print statements
    if( std::string(argv[1]).compare("Test1")==0){
      // this is test 1 from CMake
      Grid a;
      a.printGridDimension();
      a.printGridNSquares();
      return 0;
    }

    // testing 'setCellValue' 1
    if( std::string(argv[1]).compare("Test2")==0){
      // this is test 1 from CMake
      Grid a;
      a.setCellValue(0,0,999);
      return 0;
    }

    // testing 'setCellValue' 2
    if( std::string(argv[1]).compare("Test3")==0){
      // this is test 1 from CMake
      Grid a;
      a.setCellValue(0,0,2);
      a.setCellValue(0,0,3);
      return 0;
    }

  }
  
  return 0;
}
