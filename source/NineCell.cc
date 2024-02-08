
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
  cells.push_back(cell); // calls copy constructor
}

bool NineCell::resolveConstraints(){
  // resolve constaints here
  return 1;
}

