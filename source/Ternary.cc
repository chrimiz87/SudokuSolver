
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
  
  cells[index]= cell; // copy

  unsigned row = index/9;
  unsigned col = index%9;
  unsigned square = col/3; 
  ncells[row].addCell(cell);
  ncells[square+3].addCell(cell);
}

bool Ternary::resolveNineCells(){
  
  bool progress = 0;

  auto resolveSimple = [&](auto& ncell){
    progress |= ncell.resolveConstraints();
  };
  
  std::for_each( std::begin(ncells), std::end(ncells), resolveSimple ) ;

  return progress;
}
