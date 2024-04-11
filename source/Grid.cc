#include <iostream>
#include <algorithm>

#include "Grid.hh"
#include "Cell.hh"
#include "Ternary.hh"

// constructor. Creates a grid of gridDim*gridDim cells
// and calls buildTernaries to put those cells into ternaries
// by default, 'canGuess' is true, enabling the 'guessing' function.
Grid::Grid() : gridDim(9) , ternaries(6), canGuess(true) {
  // create 9x9 array of Cells on the heap, holding only shared pointers.
  for(int index=0; index<gridDim*gridDim; ++index){

    cells.emplace_back( std::make_shared<Cell>(index) );
  }

  // fill ternary objects from the cells
  buildTernaries();
}

// copy constructor. Used for the 'guessing' function of the Grid
Grid::Grid(Grid& g) : gridDim(9), ternaries(6), canGuess(true) {

  // deep copy of cells from the existing grid
  for(int i=0; i<gridDim*gridDim; ++i){
    unsigned index = cells.size();
    cells.emplace_back( std::make_shared<Cell>( *(g.cells[index]) ) );
  }

  // fill ternary objects from the cells
  buildTernaries();
}

// This function is called by the Grid constructor
// It puts each cell into two of the ternaries (one row, one column)
// and then calls Ternary::organiseCells()
void Grid::buildTernaries(){

  for(int index=0; index<gridDim*gridDim; ++index){

    // first 3 ternarys, holding rows
    unsigned rowA  = index/9; // row in the GRID
    unsigned colA  = index%9;
    unsigned ternA = rowA/3;
    unsigned ternArow = rowA%3; // row in the TERNARY
    ternaries[ternA].addCell( ternArow, colA, cells[index] );
    
    // second 3 ternarys, holding columns
    // define a left-hand (-90 degree) rotation of the Grid 

    // first column in grid is the first row of the ternary
    unsigned rowB = index%9;
    // last row in grid is the first column of the ternary
    unsigned colB = abs(int(index)/9-8);

    unsigned ternB = rowB/3;
    unsigned ternBrow = rowB%3;

    ternaries[ternB+3].addCell( ternBrow, colB, cells[index] );
  }

  // tell each ternary to organise its cells into rows and squares
  for(auto& ternary : ternaries){
    ternary.organiseCells();
  }
  
}

// This function simply prints the grid dimension
void Grid::printGridDimension(){
  std::cout << " Grid dimensions " << gridDim << std::endl;
}

// This function simply prints the number of cells in the grid
void Grid::printGridNCells(){
  std::cout << " Grid number of squares " << gridDim*gridDim << std::endl;
}

// This function simply prints the grid in a nice format.
void Grid::printGrid(){

  std::cout << "|---|---|---|---|---|---|---|---|---|" << std::endl;

  // print first 3 of the 6 ternaries (prints the full grid)
  auto ternaryprinter = [](Ternary& ternary){
    ternary.printTernary();
  };
  std::for_each( std::begin(ternaries), std::begin(ternaries)+3, ternaryprinter);
  std::cout << std::endl;
}

// this function prints the ID of each cell in the Grid.
// First it prints all the cell IDs in a line.
// Then it prints the cell IDs of each Ternary separately.
void Grid::printCellIDs(){

  // print ID of each cell
  auto printer = [](auto& cell){
    std::cout << cell->getID() << " ";
  };
  std::for_each( std::begin(cells), std::end(cells), printer);
  std::cout << std::endl;

  // print ID of each ternary
  auto ternaryprinter = [](Ternary& ternary){
    ternary.printCellIDs();
  };
  std::for_each( std::begin(ternaries), std::end(ternaries), ternaryprinter);
}

// this function sets the value of the cell with cooridnates given by
// row and column, to the value specfied by val.
// the function checks for valid 'val' and then computes the cell index
// (cellID) and calls the overloaded 'setCellValue' function below
void Grid::setCellValue(unsigned row, unsigned col, unsigned val){

  if(not checkValidValue(val)){
    std::cout << " Warning in Grid::" << __FUNCTION__ << ". val " << val
	      << " is not valid, must be from 1-9 " << std::endl;
    return; 
  }
  
  unsigned cellID = getCellID(row, col);

  setCellValue(cellID, val);
}

// this function sets the value of the cell with index 'cellID' to the
// value specfied by val. The function checks for valid 'cellID' and
// then calls Cell::setValue(...);
void Grid::setCellValue(unsigned cellID, unsigned val){
  if(not checkValidCellID(cellID)){
    std::cout << " Warning in Grid::" << __FUNCTION__
	      << ". cellID " << cellID << " is not valid." << std::endl;
    return; 
  }
  
  cells[cellID]->setValue(val);
}

unsigned Grid::getCellSolvedValue(unsigned cellID){
  if(cellID>=cells.size()){
    std::cout << " Warning in Grid::" << __FUNCTION__ << ", cell ID " << cellID
	      << " requested but it's not valid " << std::endl;
    return 0;
  }
  return cells[cellID]->getSolvedValue();
}

void Grid::setGridValues(std::vector< std::vector<unsigned> >& rows){
  if(rows.size()!=9){
    std::cout << "Warning in Grid::" << __FUNCTION__
	      << ". Cannot set the grid values with " << rows.size() << " rows " << std::endl;
    return; 
  }
  for(unsigned row=0; row<rows.size(); ++row){
    setRowValues(row, rows[row]);
  }
  
}

void Grid::setRowValues(unsigned row, std::vector<unsigned>& vals){

  if(vals.size() != 9){
    std::cout << "Warning in Grid::" << __FUNCTION__
	      << ". Cannot set a row of dimension " << vals.size() << std::endl;
    return; 
  }
  
  for(unsigned col=0; col<vals.size(); ++col){
    if(vals[col]>0){
      setCellValue(row, col, vals[col]);
    }
  }
}

inline unsigned Grid::getCellID(unsigned row, unsigned col){
  return (row*gridDim + col);
}

inline bool Grid::checkValidValue(unsigned val){
  return (val>0 && val<10);
}

inline bool Grid::checkValidCellID(unsigned cellID){
  return (cellID<cells.size());
}

inline bool Grid::checkValidRowCol(unsigned row, unsigned col){
  return (row<gridDim && col<gridDim);
}

bool Grid::resolve(){

  bool progress = false;

  // make one 'resolve' step, calling 'resolveAll' on each Ternary
  auto resolveall = [&](Ternary& tern){
    progress |= tern.resolveAll();
  };

  std::for_each( std::begin(ternaries), std::end(ternaries), resolveall );

  return progress;
}

// attempt to solve the puzzle
void Grid::solve(){
  unsigned countProgress = 0;
  bool progress = false;
  while(countProgress<3){
    // run resolve until no progress is made
    progress = resolve();

    // check if the puzzle is solved
    if(isSolved()){
      break;
    }
    
    // count lack of progress
    if(not progress){
      ++countProgress;
    }
    else{
      // reset progress counter to zero
      // if progress has been made
      countProgress=0;
    }
  }

  if(countProgress==3){
    std::cout << "Progress stalled ... ";

    // for debugging
    std::cout << " The grid looks like this: " << std::endl;
    printGrid();

    if(canGuess){
      // guess
      std::cout << " will try to guess!" << std::endl;
      bool result = guess();
      
      if(result){
	std::cout << "Solved succesfully after guessing!" << std::endl;
      }
    }
    else{
      std::cout << " this grid is a copy and cannot guess." << std::endl;
    }
      
  }
  else{
    std::cout << "Solved succesfully!" << std::endl;
  }
}

bool Grid::guess(){

  // This function allows the Grid to guess a value for any cell with only 2 options.
  // This is usually needed for the most difficult Sudoku puzzles.
  // Guesses are only supported for cells with exactly 2 possible values.

  // find cell that has exactly two options.
  std::set<unsigned> vals;
  for(unsigned i=0; i<cells.size(); ++i){
    if(cells[i]->getNPossibles()==2){
      vals = cells[i]->getSetOfPossibles();
      
      if(vals.size()!=2){
	std::cout << " Error in Grid::" << __FUNCTION__ << ", this cell has two possibles"
		  << " but the set of possibles does not have size == 2 " << std::endl;
	exit(1);
      }
      
      // for each potential value of this cell,
      // create a second grid, copy the contents of the first
      // grid into the second, and then 'guess' one of the two
      // values for this cell.
      
      // if it does not work, try the other value.

      // if neither works, continue working through the cells
      // until one of them works
      
      for(auto& val : vals){
	
	// create a second grid, using copy constructor
	Grid b(*this);
	
	// avoid chains of guessing.
	b.setCanGuess(false);

	// set the cell and value of the guess
	b.setCellValue(i, val);

	std::cout << " trying to guess. Cell " << i
		  << " was set to the value " << val << std::endl;

	// std::cout << " and the new grid looks like:" << std::endl;
	// b.printGrid();
	
	// now try to solve this grid
	b.solve();

	if(b.isSolved()){
	  std::cout << "This guess was successful!" << std::endl;

	  // std::cout << " The grid now looks like:" << std::endl;
	  // b.printGrid();

	  // copy contents of b over to the primary grid.

	  for(int j=0; j<cells.size(); ++j){
	    if(cells[j]->getNPossibles()>1){
	      // copy only cells that are not solved
	      cells[j]->setValue(b.getCellSolvedValue(j) );
	    }
	  }
	  
	  return true;
	}
	
      } // try both values
      
    } // if possibles == 2 

  } // loop over cells
  
  return false;
}

void Grid::setCanGuess(bool cg){
  canGuess = cg;
}


bool Grid::isSolved(){
  for(auto& cell : cells){
    if( not cell->isSolved())
      return false; 
  }
  return true;
}
