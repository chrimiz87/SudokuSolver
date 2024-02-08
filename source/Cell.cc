#include <iostream>

#include "Cell.hh"

Cell::Cell(unsigned ID) : cellID(ID), possibles(9, true), nPossibles(9), solvedValue(0) {
}

unsigned Cell::getID(){
  return cellID;
}

bool Cell::checkValue(unsigned val){

  // if the cell is already solved
  if(isSolved()){
    return (solvedValue == val);
  }

  return possibles[val-1];
}

void Cell::setValue(unsigned val){

  if(isSolved() && solvedValue != val){
    std::cout << " Warning in Cell::" << __FUNCTION__ << ". tried to set value " << val
	      << " but this cell is already solved with value " << solvedValue << std::endl;
  }
  
  nPossibles = 1;
  solvedValue = val;
}

bool Cell::isSolved(){
  return (nPossibles==1);
}

unsigned Cell::getSolvedValue(){
  if(not isSolved()){
    std::cout << " Warning in Cell::" << __FUNCTION__ << ". This cell is not solved. Returning zero." << std::endl;
  }
  return solvedValue;
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
