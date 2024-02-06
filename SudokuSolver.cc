#include <iostream>

#include "Grid.hh"

int main(int argc, char** argv){

  if(argc>1){
    // testing mode.

    if( std::string(argv[1]).compare("Test1")==0){
      // this is test 1 from CMake
      Grid a;
      a.printGridDimension();
      a.printGridNSquares();
      return 0;
    }
    
  }

  Grid a;
  a.printGridDimension();
  a.printGridNSquares();
  a.printGrid();

  return 0;
}
