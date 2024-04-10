#include <algorithm>
#include <cmath>

#include "Ternary.hh"

Ternary::Ternary() : cells(27), ncells(6){
}

void Ternary::printCellIDs(){

  std::cout << " printing TERNARY cells: " << std::endl;
  auto printer = [](auto& cell){
    if(cell == nullptr){
      std::cout << " NULL ";
    }
    else{
      std::cout << cell->getID() << " ";
    }
  };

  std::cout << " cells size "<< cells.size() << std::endl;
  std::for_each( std::begin(cells), std::end(cells), printer);
  std::cout << std::endl;

  auto ncellprinter = [](auto& ncell){
    ncell.printCellIDs();
  };
  std::for_each( std::begin(ncells), std::end(ncells), ncellprinter);
}


void Ternary::addCell(unsigned row, unsigned col, std::shared_ptr<Cell>& cell){

  // this function adds a cell to the Ternary. In this scope,
  // row and col refer to the row and column within the Ternary,
  // not rows and columns of the Grid.

  unsigned index = row*9 + col;
  
  // add new cell to vector of cell pointers
  cells[index] = cell; // copy
}

void Ternary::organiseCells(){

  for(int i=0; i<cells.size(); ++i){
    unsigned row = i/9;
    unsigned col = i%9;
    ncells[row].addCell(cells[i]);
    unsigned square = col/3;
    ncells[square+3].addCell(cells[i]);
  }
    
}

bool Ternary::resolveAll(){
  bool progress = false;

  // resolve simple rules on NineCell objects
  progress |= resolveNineCells();

  // resolve more complex rules on this Ternary
  progress |= resolveComplex();

  return progress;
}

bool Ternary::resolveComplex(){

  // loop over possible values
  for(unsigned poss=1; poss<10; ++poss){

    // build a 3x3 grid of whether this possible value
    // is in each set of 3 cells that define the 9x3 ternary
    bool result[3][3] = {0};
    // number of rows in each square that contain 'possible'
    unsigned nrows[3] = {0};
    // bitmask for each square, the 3 LSB represent the 3 rows
    unsigned  rows[3] = {0};

    // loop over squares to build grid
    for(unsigned sq=0; sq<3; ++sq){

      // get a square. plus 3 as the first 3 elements are the rows.
      NineCell& square = ncells[sq+3];

      // check which rows contain 'possible'
      for(unsigned r=0; r<3; ++r){
	// check one third of the square, 
	// corresponding to 3 cells in the same row
	if(square.checkThird(r,poss)){
	  result[sq][r] = 1;
	  ++nrows[sq];
	  rows[sq] |= (1<<r);
	}
      }
    }

    // loop over squares and check two rules:
    for(int sq=0; sq<3; ++sq){

      // 1. First, check for squares in which all instances of 'possible'
      //    are in the same row. In that case, no instance of 'possible'
      //    should be in that row in the other squares

      // if number of rows is 1, then the possible value
      // should be removed from the other two squares in the row.
      if(nrows[sq]==1){
	
	// use bitmask 'rows' to easily extract the row number
	unsigned row = log2(rows[sq]);
	
	// find the row that needs to be handled.
	NineCell& therow = ncells[row];
	
	// when considering rows, each square corresponds
	// to one third of the row.
	
	// remove poss from the other 2 squares of this row
	for(int sq2=0; sq2<3; ++sq2){
	  // ignore the current square
	  if(sq2 == sq){
	    continue;
	  }
	  else{
	    // remove possible from this square in the row
	    therow.removePossibleFromThird(sq2, poss);
	  }
	}
	
      } // nrows == 1
      
      // 2. Second, check if two squares only have instances of 'possible'
      //    in the same two rows. If so, the 'other' square can ONLY have
      //    possible in the 'other' row
      
      if(nrows[sq]==2){

	// the 'other' square
	unsigned thesquare = 99;

	// check if a second square has the same rows as 'sq'
	// no need to check sq2<=sq
	for(int sq2=sq+1; sq2<3; ++sq2){
	  // compare bitmask to identify two squares with 'possible'
	  // only in the same two rows!
	  if( rows[sq] != rows[sq2] ){
	    continue;
	  }
	
	  // squares sq and sq2 have 'possible' in the same two rows.
	  // now identify the 'other' square
	  
	  // find the other square.
	  for(int sq3=0; sq3<3; ++sq3){
	    if(sq3!=sq && sq3!=sq2){
	      // sq3 is the 'other' square!
	      thesquare = sq3;
	      break;
	    }
	  }
	}
	
	// thesquare is the square of interest, or 99!

	if(thesquare != 99){
	  // for the rows in rows[sq], remove possible from this square
	  for(int r2 = 0; r2<3; ++r2){
	    if( (rows[sq]<<r2)&0x1 ){
	      ncells[r2].removePossibleFromThird(thesquare, poss);
	    }
	  }
	}
	  
      } // if nrows == 2 

    }// loop over squares
    
    
  }//loop over possibles
  
  return false;
}

bool Ternary::resolveNineCells(){
  
  bool progress = 0;

  auto resolveSimple = [&](auto& ncell){
    progress |= ncell.resolveConstraints();
  };
  
  std::for_each( std::begin(ncells), std::end(ncells), resolveSimple ) ;

  return progress;
}

void Ternary::printTernary(){

  // loop over rows
  for(int row=0; row<3; ++row){
    ncells[row].printNineCell();
  }
  
}
