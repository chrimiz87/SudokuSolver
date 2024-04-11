#include <iostream>

#include "Cell.hh"

Cell::Cell(unsigned ID) : cellID(ID), possibles(9, true),
			  nPossibles(9), solvedValue(0), resolved(false) {
}

// copy constructor
Cell::Cell(Cell& c){
  cellID      = c.cellID;
  possibles   = c.possibles;
  nPossibles  = c.nPossibles;
  solvedValue = c.solvedValue;
  resolved    = c.resolved;
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

  // this is a public function that returns the solved value
  
  if(not isSolved()){
    std::cout << " Warning in Cell::" << __FUNCTION__
	      << ". This cell is not solved. Returning zero." << std::endl;
  }
  return solvedValue;
}

unsigned Cell::findSolvedValue(){

  // this is a private function used internally by Cell to set the solved
  // value once there is only one possible remaining.
  
  for(int idx=0; idx<possibles.size(); ++idx){
    if(possibles[idx]) return (idx+1); // return value not index!
  }
  return 0;
}

bool Cell::removePossible(unsigned val){

  // this function removes the possible specified by 'val'.
  // if this leads to there being only one possible, the solved
  // value is set using the 'findSolvedValue' function.
  
  // do nothing is the cell is already solved
  bool progress = false;
  if(isSolved()){
    return progress;
  }

  // check if the possible value 'val' is still possible
  if(possibles.at(val-1)){
    // this value is possible, remove it 
    possibles[val-1] = false;
    // reduce the number of possibles 
    --nPossibles;
    // record the progress
    progress = true;
    // check if the cell has now been solved (nPossibles == 1)
    // if so, find the solved value and record it.
    if(isSolved()){
      solvedValue = findSolvedValue();
      // output message informing of the progress
      std::cout << " cell " << cellID << " (" << cellID%9 << "," << cellID/9
		<< ") was solved to value " << solvedValue
		<< " after removing value " << val
		<< std::endl;
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

bool Cell::checkPossible(unsigned val){

  // only 1--9 are valid possibles
  if(val==0 || val>10){
    std::cout << " Warning in Cell::" << __FUNCTION__ << ", the possible "
	      << val << " is not valid." << std::endl;
    return false;
  }

  // the -1 accounts for difference between value and index.
  return possibles[val-1];
}
