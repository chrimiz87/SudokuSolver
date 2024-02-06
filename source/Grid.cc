#include <iostream>

#include "Grid.hh"

Grid::Grid() : gridDim(9) {
  cells.resize(gridDim*gridDim);
}

void Grid::printGridDimension(){
  std::cout << " Grid dimensions " << gridDim << std::endl;
}

void Grid::printGridNSquares(){
  std::cout << " Grid number of squares " << gridDim*gridDim << std::endl;
}

void Grid::printGrid(){

  unsigned vals[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
  
  std::cout << "|---|---|---|---|---|---|---|---|---|" << std::endl;
  
  // loop over rows
  for(int x=0; x<gridDim; ++x){

    // 3 times for each row
    for(int i=0; i<3; ++i){
      
      std::cout << "|" ;
      // loop over columns
      for(int y=0; y<gridDim; ++y){
	Cell& c = cells[x*gridDim + y];
	
	// check one set of 3 values for this cell
	for( unsigned& val : vals[i]){
	  ( c.checkValue(val) ) ? std::cout << val : std::cout << " ";
	}
	std::cout << "|" ;
      }
      std::cout << std::endl;
    }
    std::cout << "|---|---|---|---|---|---|---|---|---|" << std::endl;
  }
}
