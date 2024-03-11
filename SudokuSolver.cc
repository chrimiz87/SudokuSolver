#include <iostream>


#include "Grid.hh"
#include "Ternary.hh"

int main(){

  Grid a;

  // some basic printouts
  if(false){
    a.printGridDimension();
    a.printGridNSquares();
    a.printGrid();

    a.setCellValue(0,0,1);
    a.setCellValue(0,1,2);
    a.setCellValue(0,2,3);

    a.printGrid();

    // a.printCellIDs();

    a.resolve();

    a.printGrid();

    a.solve();

    a.printGrid();
  }

  // first attempt at a real puzzle

  // easy difficulty, passes with just simple rules on NineCell
  // std::vector< std::vector<unsigned> > gridcontent ={
  //   {0,2,9,3,7,0,5,0,1},
  //   {0,6,7,0,0,0,4,2,0},
  //   {0,0,4,0,0,0,3,7,0},
  //   {2,0,6,5,3,0,9,0,0},
  //   {1,0,8,0,4,0,2,0,7},
  //   {9,4,0,0,2,0,0,1,3},
  //   {0,5,0,4,0,6,0,3,0},
  //   {0,0,0,2,1,0,7,0,0},
  //   {4,0,0,0,5,0,0,9,0},
  // };

  // extreme difficulty
  std::vector< std::vector<unsigned> > gridcontent ={
    {1,0,0,0,0,0,0,8,0},
    {2,3,7,0,0,0,0,0,0},
    {6,0,0,0,0,0,4,1,0},
    {0,0,3,0,0,6,0,0,0},
    {0,9,0,0,1,0,0,0,0},
    {0,0,0,0,0,4,0,5,9},
    {0,0,0,0,0,0,7,0,0},
    {0,6,0,3,0,0,2,0,0},
    {0,0,0,2,7,0,0,0,1},
  };
  a.setGridValues(gridcontent);

  a.printGrid();

  a.resolve();
  // a.resolve();
  // a.resolve();
  // a.resolve();
  std::cout << " After resolve 1 " << std::endl;

  a.printGrid();\

  std::cout << std::endl;
  std::cout << " Starting resolve 2 " << std::endl;
  a.resolve();
  std::cout << " After resolve 2 " << std::endl;
  a.printGrid();

  std::cout << std::endl;
  std::cout << " Starting resolve 3 " << std::endl;
  a.resolve();
  std::cout << " After resolve 3 " << std::endl;
  a.printGrid();

  a.solve();
  a.printGrid();

  return 0;
}
