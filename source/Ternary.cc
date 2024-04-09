#include <algorithm>

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

void Ternary::addCell(unsigned index, std::shared_ptr<Cell>& cell){

  // add new cell to vector of cell pointers
  cells[index] = cell; // copy

  // add new cell to the NineCell container,
  // which holds NineCells for rows and for squares

  // add to NineCell representing a row
  unsigned row = index/9;
  ncells[row].addCell(cell);

  // add to NineCell representing a square, the +3 is because
  // the first 3 elements are the NineCells representing rows
  unsigned col = index%9;
  unsigned square = col/3; 
  ncells[square+3].addCell(cell);
}

bool Ternary::resolveAll(){
  bool progress = false;

  // resolve simple rules on NineCell objects
  std::cout << " Starting resolve simple " << std::endl;
  progress |= resolveNineCells();

  // resolve more complex rules on this Ternary
  std::cout << " Starting resolve complex " << std::endl;
  printTernary();  
  std::cout << std::endl;
  progress |= resolveComplex();
  printTernary();

  return progress;
}

bool Ternary::resolveComplex(){

  // loop over possible values
  for(int poss=1; poss<10; ++poss){

    // std::cout << " possible = " << poss << std::endl;

    // loop over squares
    for(int sq=0; sq<3; ++sq){
      // get a square. plus 3 as the first 3 elements are the rows.
      NineCell& square = ncells[sq+3];
      // std::cout << " square = " << sq << std::endl;
      
      // check if the possible exists in only one row of the square
      unsigned nrows=0;
      unsigned row=99;
      for(int r=0; r<3; ++r){
	// check one third of the square, 
	// corresponding to 3 cells in the same row
	if(square.checkThird(r,poss)){
	  // at least one cell in this row contains the possible value

	  // increment number of rows where the possible was found
	  ++nrows;
	  // store which row it was in.
	  row = r;
	}
      }

      // std::cout << " nrows = " << nrows << " row = " << row << std::endl;


      // if number of rows is 1, then the possible value
      // should be removed from the other two squares in the row.
      if(nrows==1){

	// std::cout << " will remove " << poss << " !" << std::endl;

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
