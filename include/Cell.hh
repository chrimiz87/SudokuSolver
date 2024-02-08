#ifndef CELL_HH
#define CELL_HH

// Header file for Cell class

// The cell class represents one cell of the Sudoku puzzle
// It holds a vector of bool contain the possible values of this containing N bools,
// for values 1-N. The default value is 'true', meaning the value is possible.
// As the game progresses, the number of 'true's should reduce,
// until there is only one possible value.
// The remaining number of possibles is stored. The cell is solved when the number of
// possible values is equal to 1.
// The last remaining value is stored.

// The cells are only accessed from the Grid class. The design is such that all checks
// on the validity of inputs (values between 1 and 9, cell IDs from 0 to 80, ...) are
// handled in the Grid class.

#include <vector>

class Cell{
public:
  Cell() = delete;
  Cell(unsigned ID);

  unsigned getID();

  bool checkValue(unsigned val);

  void setValue(unsigned val);

  bool isSolved();
  unsigned getSolvedValue();

private:

  unsigned cellID;
  std::vector<bool> possibles;
  unsigned nPossibles;
  unsigned solvedValue;
};

#endif // CELL_HH
