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
  unsigned maxset = n_unsolved/2;

  unsigned mode = 0; 
  std::set<unsigned> theset;
  std::vector<unsigned> cellindexes;
  for(unsigned setsize = 1; setsize<=maxset; ++setsize){
    
    // first run with mode '0'
    // in this mode, check for group of cells with the same set of possibles
    std::cout <<"  MODE 0 " << std::endl;
    mode = 0;
    theset.clear();
    cellindexes.clear();
    progress |= checkForSets(mode, setsize, theset, cellindexes);

    // second run with mode '1'
    // in this mode, check for group of 'possibles' in the same set of cells
    std::cout <<"  MODE 1 " << std::endl;
    mode = 1;
    theset.clear();
    cellindexes.clear();
    progress |= checkForSets(mode, setsize, theset, cellindexes);
  }
  
  return progress;
}

bool NineCell::checkForSetsOfOne(){
  bool progress = false;
  std::vector< std::shared_ptr<Cell> >::iterator iti = std::begin(cells);
  for( ; iti != std::end(cells); ++iti){
    
    if( (*iti)->isSolved()){
      // this cell is solved. Propagate this information to other cells in the NineCell
      std::vector< std::shared_ptr<Cell> >::iterator itj = std::begin(cells);
      for( ; itj != std::end(cells); ++itj){
	progress |= (*itj)->removePossible( (*iti)->getSolvedValue() ); // value of 
      }
    }
  }
  return progress; 
}

bool NineCell::checkForSets(unsigned mode, unsigned& setsize, std::set<unsigned>& theset, std::vector<unsigned>& indexes){

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

  bool progress = false;
  
  // first relevant index for the set check
  unsigned firstindex = 0;
  if(mode==0 && indexes.size()){
    firstindex = indexes.back() + 1;
  }

  // i and firstindex are the index in the cell array (mode==0) or the
  // possible values to be considered (mode==1)
  for(unsigned i=firstindex; i<cells.size(); ++i){
    
    // get the set for this cell
    std::set<unsigned> tmp; 
    if(mode==0){
      // tmp is a set of possible values for this cell
      tmp = cells[i]->getSetOfPossibles();
    }
    else{
      // tmp is a set of possible cells for this value
      for(unsigned cell = 0; cell<9; ++cell){
	if(cells[cell]->checkValue(i+1)){
	  tmp.insert(cell);
	}
      }
	
    }

    if(tmp.size() == 0){
      std::cout << " Warning in NineCell::" << __FUNCTION__ << ". A set of possible values"
		<< " with zero size was received. This should not be possible" << std::endl;
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

    // union of sets.
    std::set<unsigned> theunion = theset;
    theunion.merge(tmp);

    if(theunion.size()>setsize){
      // this cannot be a set of size 'setsize'. move to the next cell
      continue;
    }

    // these are the indexes of cells in the group (mode==0)
    // or the group of possible values (mode==1)
    std::vector<unsigned> unionindexes = indexes; 
    unionindexes.push_back(i + mode);

    // win condition is 'N' cells forming a union of 'N' possible values (mode==0)
    // or
    // 'N' possibilities found exclusively in a union of 'N' cells (mode==1)
    if(theunion.size() == setsize && unionindexes.size() == setsize){
      if(mode==0){
	removeValues( theunion, unionindexes );
      }
      else{
	removeCells( theunion, unionindexes );
      }
    }
    else{
      // this can be a set of size 'setsize', continue searching
      progress |= checkForSets(mode, setsize, theunion, unionindexes);
    }
  }
  return progress; // to continue searching
}

void NineCell::removeValues(std::set<unsigned>& values, std::vector<unsigned>& indexes){

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

void NineCell::removeCells(std::set<unsigned>& values, std::vector<unsigned>& indexes){

  // this function removes all possibles that are not in 'indexes'
  // from the cells in 'values'

  std::cout << " cell IDs ";
  for( auto& idx :  values)
    std::cout << idx << " ";
  std::cout << " possible values ";
  for(auto& val : indexes){
    std::cout << val << " ";
  }
  std::cout << std::endl;

  for( auto& idx : values){

    for(unsigned p = 1; p<10; ++p){
      if( std::find(std::begin(indexes), std::end(indexes), p) == std::end(indexes) ){
	// this possible is not in 'indexes'
	cells[idx]->removePossible(p);
      }
    }
  }
  
}

void NineCell::setPossibles(unsigned index, std::vector<unsigned>& possibles){
  if(index>cells.size()){
    std::cout << " Warning in NineCell::" << __FUNCTION__ << ", Cannot set possibles "
	      << " for index " << index << " which is invalid " << std::endl;
  }
  
  for(unsigned val = 1; val<10; ++val){    
    if( std::find(std::begin(possibles), std::end(possibles), val) == std::end(possibles) ){
      cells[index]->removePossible(val);
    }
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
