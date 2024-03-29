#include <iostream>
#include <algorithm>

#include "Grid.hh"
#include "Cell.hh"
#include "Ternary.hh"

Grid::Grid() : gridDim(9) , ternaries(6) {
  // create 9x9 array of Cells on the heap, holding only shared pointers.
  for(int i=0; i<gridDim*gridDim; ++i){

    unsigned index = cells.size();
    cells.emplace_back( std::make_shared<Cell>(index) );

    // first 3 ternarys, holding rows
    unsigned rowA  = index/9; // row in the GRID
    unsigned colA  = index%9;
    unsigned ternA = rowA/3;
    unsigned ternArow = rowA%3; // row in the TERNARY
    ternaries[ternA].addCell( ternArow*9+colA, cells.back() );
    
    // second 3 ternarys, holding columns
    // the indexing just needs rows and columns to be swapped 
    unsigned rowB = colA;
    unsigned colB = rowA;
    unsigned ternB = rowB/3;
    unsigned ternBrow = rowB%3;
    ternaries[ternB+3].addCell( ternBrow*9+colB, cells.back() );
  }
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
  for(int row=0; row<gridDim; ++row){

    // 3 times for each row
    for(int i=0; i<3; ++i){
      
      std::cout << "|" ;
      // loop over columns
      for(int col=0; col<gridDim; ++col){
	
	std::shared_ptr<Cell> c( cells[getCellID(row,col)]) ;
	
	// check one set of 3 values for this cell
	for( unsigned& val : vals[i]){
	  ( c->checkValue(val) ) ? std::cout << val : std::cout << " ";
	}
	std::cout << "|" ;
      }
      std::cout << std::endl;
    }
    std::cout << "|---|---|---|---|---|---|---|---|---|" << std::endl;
  }
}

void Grid::printCellIDs(){
  auto printer = [](auto& cell){
    std::cout << cell->getID() << " ";
  };
  
  std::for_each( std::begin(cells), std::end(cells), printer);
  std::cout << std::endl;

  auto ternaryprinter = [](Ternary& ternary){
    ternary.printCellIDs();
  };
  std::for_each( std::begin(ternaries), std::end(ternaries), ternaryprinter);
}

void Grid::setCellValue(unsigned row, unsigned col, unsigned val){

  if(not checkValidValue(val)){
    std::cout << " Warning in Grid::" << __FUNCTION__ << ". val " << val
	      << " is not valid, must be from 1-9 " << std::endl;
    return; 
  }
  
  unsigned cellID = getCellID(row, col);
  
  if(not checkValidCellID(cellID)){
    std::cout << " Warning in Grid::" << __FUNCTION__
	      << ". cellID " << cellID << " is not valid." << std::endl;
    return; 
  }

  cells[cellID]->setValue(val);
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

  std::cout << " Finished solving the puzzle ";
  if(countProgress==3){
    std::cout << "due to progress having stalled" << std::endl;
  }
  else{
    std::cout << "successfully!" << std::endl;
  }
}

bool Grid::isSolved(){
  for(auto& cell : cells){
    if( not cell->isSolved())
      return false; 
  }
  return true;
}
