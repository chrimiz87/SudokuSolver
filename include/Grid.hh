#ifndef GRID_HH
#define GRID_HH
// Header file for Grid class.

// The grid class contains a 9*9 grid of cells that make up the Sudoku puzzle.
// The grid dimension, gridDim = 9, so 9*9 = 81 cells in total.
//
// The grid is created with a gridDim = 9.
// The content of cells can be set via the grid. The input must be sanitised
// to ensure a reasonable puzzle. 
// The grid can be drawn to show the content of the grid.

#include <vector>

#include "Cell.hh"

class Grid{
  
public:
  Grid();

  void printGridDimension();
  void printGridNSquares();
  void printGrid();

private:
  unsigned gridDim;
  std::vector< Cell > cells;
};

#endif // GRID_HH
