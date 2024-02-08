#include <iostream>

#include "Grid.hh"

int main(){


  Grid a;
  a.printGridDimension();
  a.printGridNSquares();
  a.printGrid();

  a.setCellValue(0,0,1);
  a.setCellValue(0,1,2);
  a.setCellValue(0,2,3);

  a.printGrid();  
  
  return 0;
}
