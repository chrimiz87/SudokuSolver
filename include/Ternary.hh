#ifndef TERNARY_HH
#define TERNARY_HH

// Ternary class holds a 3x9 set of cells, making up 1/3 of the Sudoku puzzle
// It is important to resolve more complex constraints.
// It holds 27 Cell shared pointers and 6 NineCell objects.
// The first 3 NineCell objects correspond to rows, the latter 3 correspond to squares
// The resolving of constraints in the Ternary class are identical whether or not
// the cells inside correspond to rows or columns of the Sudoku puzzle.
// The more simple constraints will be resolved via the NineCell objects
// The more complex constraints will be resolvedd in this class.

#include "Cell.hh"
#include "NineCell.hh"

class Ternary{

public: 

  Ternary();

  void printCellIDs();

  void addCell(unsigned index, std::shared_ptr<Cell>& cell);

  bool resolveAll();
  bool resolveComplex();
  bool resolveNineCells();

  void printTernary();

private:
  std::vector< std::shared_ptr<Cell> > cells;
  std::vector< NineCell > ncells;
};

#endif // TERNARY_HH
