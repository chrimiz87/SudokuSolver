#include <iostream>

#include "Grid.hh"

int main(int argc, char** argv){

  if(argc>1){
    // testing mode.

    // testing basic print statements
    if( std::string(argv[1]).compare("Test1")==0){
      Grid a;
      a.printGridDimension();
      a.printGridNSquares();
      return 0;
    }

    // testing 'setCellValue' setting an invalid value
    if( std::string(argv[1]).compare("Test2")==0){
      Grid a;
      a.setCellValue(0,0,999);
      return 0;
    }

    // testing 'setCellValue' setting the value twice with different values
    if( std::string(argv[1]).compare("Test3")==0){
      Grid a;
      a.setCellValue(0,0,2);
      a.setCellValue(0,0,3);
      return 0;
    }

  }
  
  return 0;
}
