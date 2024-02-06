#include <iostream>

#include "Cell.hh"

Cell::Cell() : possibles(9, true), nPossibles(9), solvedValue(0) {
}

bool Cell::checkValue(unsigned val){
  unsigned tmp = val-1; // convert from 'user' 1-9 to vector index 0-8
  if(tmp>=0 && tmp<possibles.size()){
    return possibles[tmp];
  }
  std::cout << " Warning. Tried to access 'possible' value " << val
	    << " which is not in the range 1 -- " << possibles.size()+1 << std::endl;
  return false;
}
