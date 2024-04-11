#include <algorithm>
#include <set>

#include "NineCell.hh"

void NineCell::printCellIDs(){

  std::cout << " printing NINECELL cells " << std::endl;
  auto printer = [](auto& cell){
    std::cout << cell->getID() << " ";
  };
  
  std::for_each( std::begin(cells), std::end(cells), printer);
  std::cout << std::endl;
}

void NineCell::addCell(std::shared_ptr<Cell>& cell){
  if(cells.size()<9){
    cells.push_back(cell); // calls copy constructor
  }
  else{
    std::cout << " Warning in NineCell::" << __FUNCTION__
	      << ". Cannot add more than 9 cells" << std::endl;
  }  
}

bool NineCell::resolveConstraints(){

  // this function resolves constraints on this NineCell object.
  // it runs a 'set checker' function in two modes.
  // 
  // the first mode (0) checks for sets of N cells that only contain
  // the same N possible values (or a subset), in which case no other
  // cells can contain any of the N values.
  //
  // the second mode (1) checks for sets of N values that are only
  // possible in a set of N cells (or a subset), in which case those
  // cells must contain only the N values.
  
  bool progress = false;

  progress |= setChecker(0);
  progress |= setChecker(1);

  return progress;
}

bool NineCell::setChecker(unsigned mode){
  
  // The most simple NineCell constraint is to check if there is a cell that is 
  // solved (one possible value) and ensure that this value does not appear in
  // any other cell.
  // A more general statement is that any group of N cells that contain the same
  // set of possible values (or a subset of them) means that all cells outside
  // of the group cannot contain any number in the set. The simple example
  // above is the limiting case where the group contains just one cell.
  // Sets with sizes from 1 to MAXSET must be checked, where MAXSET is half the
  // number of unsolved cells in the NineCell.

  // Probably checking up to MAXSET is not needed in most cases. Possibly the
  // code can therefore be improved by setting a variable MAXSET that is
  // increased if the progress stalls, before starting to guess values.
  
  bool progress = false;

  auto counter = [&](std::shared_ptr<Cell>& cellptr){
    return (not cellptr->isSolved());
  };
  
  // count number of unsolved cells
  unsigned n_unsolved = std::count_if(std::begin(cells), std::end(cells) , counter);

  if(n_unsolved == 0){
    // if everything is solved, nothing to do
    return progress;
    
  }
  else if(n_unsolved == 1){
    // if there is only one unsolved cell, solution is trivial
    // find the unsolved cell, and remove the solved values
    // from the other cells

    auto isunsolved = [](auto& cell){
      return not cell->isSolved();
    };
    auto unsolvedcell = std::find_if( std::begin(cells), std::end(cells), isunsolved);
    
    auto removeothervalues = [&](auto& cell){
      if(cell != (*unsolvedcell) ){
	progress |= (*unsolvedcell)->removePossible( cell->getSolvedValue() );
      }
    };
    std::for_each(std::begin(cells), std::end(cells), removeothervalues);
  }
  else{
    unsigned maxset = n_unsolved/2;

    std::set<unsigned> setA;
    std::set<unsigned> setB;
    for(unsigned setsize = 1; setsize<=maxset; ++setsize){
    
      // first run with mode '0'
      // in this mode, check for group of cells with the same set of possibles
      setA.clear();
      setB.clear();
      progress |= checkForSets(mode, setsize, setA, setB);
    }
  }
  
  return progress;
}

bool NineCell::checkForSets(unsigned mode, unsigned& setsize, std::set<unsigned>& setA, std::set<unsigned>& setB){

  // This code looks for groups of N cells that contain N possible values between them
  // (i.e. the Union of their possible values has size == N)
  // When this is true, it means those values are not possible for any cell in the NineCell that
  // is not a member of the group.
  // 1. check each cell if the number of possibles is equal or less than the setsize  
  // 2. if yes, build the union of an input set, and the set from this cell.
  //    a) if larger than setsizse, cannot be a set
  //    b) if equal to setsize, the set has been found and the values in the set should be
  //       removed from the other cells in the NineCell (the cells not in the group)
  //    c) if less than setsize, keep searching to try and complete the set (recursive)

  // in MODE==0, setA == values and setB == indexes.
  // in MODE==1, setA == indexes and setB == values.
  
  bool progress = false;
  
  // first relevant index for the set check
  unsigned first = mode; // 0 or 1 
  unsigned last  = cells.size() + mode; // (0..8) or (1..9)

  // if not the first level of recursion
  if(setB.size()){
    first = (*setB.rbegin())+1;
  }

  // i and first are the index in the cell array (mode==0) or the
  // possible values to be considered (mode==1)
  for(unsigned i=first; i<last; ++i){
    
    // get the set for this cell
    std::set<unsigned> tmp; 
    if(mode==0){
      // tmp is a set of possible values for this cell
      tmp = cells[i]->getSetOfPossibles();
    }
    else{
      // tmp is a set of possible cells for this value
      for(unsigned c=0; auto& cell : cells){
	if(cell->checkValue(i)){
	  tmp.insert(c);
	}
	++c;
      }
    }

    if(tmp.size() == 0){
      std::cout << " Error in NineCell::" << __FUNCTION__ << ". A set of possible values"
		<< " with zero size was received. This should not be possible" << std::endl;
      exit(1);
    }
    
    // check number of possibles for this cell (mode==0)
    // or cells for this possible value (mode==1)
    if(tmp.size() > setsize){
      // no point checking further
      continue;
    }

    if(tmp.size()==1 && setsize>1){
      // no point building sets with single values in a cell,
      // unless we are looking for sets of 1, of course
      continue;
    }

    // union of setA with the possible cells (mode==0) or values (mode==1).
    std::set<unsigned> unionSetA = setA;
    unionSetA.merge(tmp); // union of setA and 'tmp'
    
    if(unionSetA.size()>setsize){
      // this cannot be a set of size 'setsize'. move to the next cell
      continue;
    }

    // these are the indexes of cells in the group (mode==0)
    // or the group of possible values (mode==1)
    std::set<unsigned> newSetB = setB;
    newSetB.insert(i);
    
    // win condition is 'N' cells forming a union of 'N' possible values (mode==0)
    // or
    // 'N' possibilities found exclusively in a union of 'N' cells (mode==1)
    if(unionSetA.size() == setsize && newSetB.size() == setsize){
      if(mode==0){
	removeValues( unionSetA, newSetB );
      }
      else{
	removeCells( unionSetA, newSetB );
      }
    }
    else{
      // this can be a set of size 'setsize', continue searching
      progress |= checkForSets(mode, setsize, unionSetA, newSetB);
    }
  }
  return progress; // to continue searching
}

void NineCell::removeValues(std::set<unsigned>& values, std::set<unsigned>& indexes){

  // this function removes all 'values' from cells that are not in 'indexes'
  
  for( unsigned idx=0; idx<cells.size(); ++idx){
    // find if this cell is NOT in the group 
    if( std::find(std::begin(indexes), std::end(indexes), idx) == std::end(indexes) ){
      
      // if not in the group, removes 'values' from it
      for(auto& p: values){
	// remove all values in the set from cells not in the group.
	cells[idx]->removePossible(p);
      }
    }
  }
}

void NineCell::removeCells(std::set<unsigned>& indexes, std::set<unsigned>& values){

  // this function removes all possibles that are not in 'values'
  // from the cells in 'indexes'

  for(auto& idx : indexes){

    for(unsigned p = 1; p<10; ++p){
      if( std::find(std::begin(values), std::end(values), p) == std::end(values) ){
	// this possible is not in 'indexes'
	cells[idx]->removePossible(p);
      }
    }
  }
  
}

void NineCell::setPossibles(unsigned index, std::set<unsigned>& possibles){

  // this function is used for testing NineCell objects. The user can set
  // the possible value(s) of a given cell
  
  if(index>cells.size()){
    std::cout << " Warning in NineCell::" << __FUNCTION__ << ", Cannot set possibles "
	      << " for index " << index << " which is invalid " << std::endl;
  }

  std::cout << " index " << index << " possibles ";
  for( auto& p : possibles){ std::cout << p << " "; }
  std::cout << std::endl;
  
  for(unsigned val = 1; val<10; ++val){    
    if( std::find(std::begin(possibles), std::end(possibles), val) == std::end(possibles) ){
      cells[index]->removePossible(val);
    }
  }
}

bool NineCell::checkThird(unsigned third, unsigned possible){

  // value of 'third' must be 0,1,2
  if(third>2){
    std::cout << " Warning in NineCell::" << __FUNCTION__ << ", cannot choose"
	      << " a third with value " << third << std::endl;
    return false;
  }

  // this checks cells in one third (3) of the (9) cells
  // for the possible value, setting response to 'true' if found
  bool response = false;
  for(int i=0+3*third; i<3+3*third; ++i){
    response |= cells[i]->checkPossible(possible);
  }

  // return true if one cell in this third has the possible value
  return response;
}

void NineCell::removePossibleFromThird(unsigned third, unsigned possible){
  for(int i=0+3*third; i<3+3*third; ++i){
    cells[i]->removePossible(possible);
  }
}

void NineCell::printPossibles(){
  unsigned idx=0;
  for(auto& cell : cells){
    std::cout << " Cell " << idx << " possibles = ";
    std::set<unsigned> possibles = cell->getSetOfPossibles();
    for(auto& poss : possibles){
      std::cout << poss << " ";
    }
    std::cout << std::endl;
    ++idx;
  }
}

void NineCell::printNineCell(){

  unsigned vals[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };

  // 3 times for each row
  for(int i=0; i<3; ++i){
    
    std::cout << "|" ;
    // loop over columns
    for(int col=0; col<9; ++col){
      // check one set of 3 values for this cell
      for( unsigned& val : vals[i]){
	( cells[col]->checkValue(val) ) ? std::cout << val : std::cout << " ";
      }
      std::cout << "|" ;
    }
    std::cout << std::endl;
  }
  std::cout << "|---|---|---|---|---|---|---|---|---|" << std::endl;
  
}
