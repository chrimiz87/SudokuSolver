#include <iostream>

#include "Cell.hh"

Cell::Cell(unsigned ID) : cellID(ID), possibles(9, true),
			  nPossibles(9), solvedValue(0), resolved(false) {
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
    return;
  }

  if(val == 0){
    // should never happen
    std::cout << " Warning in Cel::" << __FUNCTION__ << ". Tried to set value " << val
	      << " which is not valid. " << std::endl;
    return;
  }

  possibles.clear();
  possibles.resize(9,false);  
  possibles[val-1]=true;
  nPossibles = 1;
  solvedValue = val;
}

bool Cell::isSolved(){
  return (nPossibles==1);
}

unsigned Cell::getSolvedValue(){
  if(not isSolved()){
    std::cout << " Warning in Cell::" << __FUNCTION__
	      << ". This cell is not solved. Returning zero." << std::endl;
  }
  return solvedValue;
}

unsigned Cell::findSolvedValue(){
  for(int idx=0; idx<possibles.size(); ++idx){
    if(possibles[idx]) return (idx+1); // return value not index!
  }
  return 0;
}

bool Cell::removePossible(unsigned val){
  // std::cout << " removing " << val << std::endl;
  bool progress = false;
  if(isSolved()){
    return progress;
  }
  if(possibles.at(val-1)){ // this value is possible
    possibles[val-1] = false;
    --nPossibles;
    progress = true;
    if(nPossibles == 1){
      solvedValue = findSolvedValue();
      std::cout << " cell " << cellID << " (" << cellID%9 << "," << cellID/9
		<< ") was solved to value " << solvedValue << " after removing value " << val << std::endl;
    }
  }
  return progress;
}

unsigned Cell::getNPossibles(){
  return nPossibles;
}

std::set<unsigned> Cell::getSetOfPossibles(){

  std::set<unsigned> tmp;
  
  for(unsigned i=0; i<possibles.size(); ++i){
    if(possibles[i]){
      tmp.insert(i+1); //emplace_hint( tmp.end(), i+1);
    }
  }
  
  return tmp;
}
