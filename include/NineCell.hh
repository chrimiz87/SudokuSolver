#ifndef NINECELL_HH
#define NINECELL_HH

// The NineCell class holds a collection of nine cells. 
// Nine cells collections handle rows, columns, and 3x3 squares
// This class also resolves any constraints on the cells.
// Constraints include, for example, that if one cell must be '3', no other cell can possibly be '3'
// These simple constraints work the same for rows, columns and 3x3 squares of cells.

// This class contains a vector of shared pointers to the Cells held by the Grid.

#include <iostream>
#include <memory>

#include "Cell.hh"

class NineCell{

public:

  // trivial constructor.
  NineCell() {};

  void printCellIDs();
  
  void addCell(std::shared_ptr<Cell>& cell);
  
  bool resolveConstraints();

  bool checkForSetsOfOne();
  bool checkForSets(unsigned mode, unsigned& setsize, std::set<unsigned>& theset, std::vector<unsigned>& indexes);
  void removeValues(std::set<unsigned>& values, std::vector<unsigned>& indexes);
  void removeCells(std::set<unsigned>& values, std::vector<unsigned>& indexes);

  void setPossibles(unsigned index, std::vector<unsigned>& possibles);

  void printPossibles();

private:
  std::vector< std::shared_ptr<Cell> > cells;
};

#endif // NINECELL_HH
