#ifndef GRID_HH
#define GRID_HH
// Header file for Grid class.

// The grid class contains a 9*9 grid of cells that make up the Sudoku puzzle.
// The grid dimension, gridDim = 9, so 9*9 = 81 cells in total.
//
// The grid is created with a gridDim = 9.
// The content of cells can be set via the grid. The input must be sanitised
// to ensure a reasonable puzzle. 
// The grid can be printed to show the content of the grid.

#include <vector>
#include <memory>

#include "Cell.hh"
#include "Ternary.hh"

class Grid{
  
public:
  Grid();

  // copy constructor
  Grid(Grid& g);

  void buildTernaries();

  void printGridDimension();
  void printGridNCells();
  void printGrid();
  void printCellIDs();

  void setGridValues(std::vector< std::vector<unsigned> >& vals);
  void setRowValues(unsigned row, std::vector<unsigned>& vals);
  void setCellValue(unsigned row, unsigned col, unsigned val);
  void setCellValue(unsigned cellID, unsigned val);

  unsigned getCellSolvedValue(unsigned cellID);

  inline unsigned getCellID(unsigned row, unsigned col);
  inline std::pair<unsigned, unsigned> getCellRowCol(unsigned cellID);
  
  inline bool checkValidValue(unsigned val);
  inline bool checkValidCellID(unsigned cellID);
  inline bool checkValidRowCol(unsigned row, unsigned col);

  bool resolve();
  void solve();

  bool guess();
  void setCanGuess(bool canGuess);

  bool isSolved();
  
private:
  unsigned gridDim;
  std::vector< Ternary > ternaries;
  bool canGuess;
  std::vector< std::shared_ptr<Cell> > cells;
};

#endif // GRID_HH
