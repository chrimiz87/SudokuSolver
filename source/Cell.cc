#include <iostream>

#include "Cell.hh"

Cell::Cell() : possibles(9, true), nPossibles(9), solvedValue(0) {
}

bool Cell::checkValue(unsigned val){

  // if the cell is already solved
  if(nPossibles==1){
    return (solvedValue == val);
  }
  
  unsigned tmp = val-1; // convert from 'user' 1-9 to vector index 0-8
  if(tmp>=0 && tmp<possibles.size()){
    return possibles[tmp];
  }
  std::cout << " Warning. Tried to access 'possible' value " << val
	    << " which is not in the range 1 -- " << possibles.size()+1 << std::endl;
  return false;
}

void Cell::setValue(unsigned val){

  if(nPossibles==1 && solvedValue != val){
    std::cout << " Warning Cell::setValue. tried to set value " << val
	      << " but this cell is already solved with value " << solvedValue << std::endl;
  }
  
  if(val==0 || val>9){
    std::cout << " Warning in Cell::setValue. val " << val
	      << " not valid, must be from 1-9 " << std::endl;
    return; 
  }
  
  nPossibles = 1;
  solvedValue = val;
}
