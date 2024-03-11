#include <iostream>
#include <fstream>
#include "NineCell.hh"

int main(){

  std::ofstream out("NineCellTester.txt");
  std::streambuf *coutbuf  = std::cout.rdbuf(); // save cout buffer
  std::cout.rdbuf(out.rdbuf()); // redirect cout to 'out' file 
  
  // this program is for testing the NineCell class.
  NineCell n;
  for(unsigned i=0; i<9; ++i){
    auto a = std::make_shared<Cell>(i);
    n.addCell(a);
  }

  // Test 1. Check print function
  n.printCellIDs();

  // Test 2. Try adding a 10th cell
  auto a = std::make_shared<Cell>(9);
  n.addCell(a);

  // Test 3. Test 'print possibles' function
  n.printPossibles();
  
  // Test 4. Set possibles for a cell
  std::vector<unsigned> valsA = {0,1,2};
  n.setPossibles(4, valsA);
  n.setPossibles(6, valsA);
  n.printPossibles();

  // Test 5. Test 'remove values' fucntion
  std::set<unsigned> valsB = {1,2,3};
  std::vector<unsigned> indexes = {4,5,6};
  n.removeValues(valsB, indexes);
  n.printPossibles();
  
  // Test 6. Test 'resolve' function with elaborate example
    
  std::vector<unsigned> poss;
  poss = {4,5};
  n.setPossibles(0, poss);
  poss = {3};
  n.setPossibles(1, poss);
  poss = {5,8};
  n.setPossibles(2, poss);
  poss = {1,2,4,5,7,8};
  n.setPossibles(3, poss);
  poss = {9};
  n.setPossibles(4, poss);
  poss = {1,2};
  n.setPossibles(5, poss);
  poss = {1,2,4,5,8};
  n.setPossibles(6, poss);
  poss = {6};
  n.setPossibles(7, poss);
  poss = {4,5,8};
  n.setPossibles(8, poss);

  n.printPossibles();

  n.resolveConstraints();

  n.printPossibles();
  
  n.resolveConstraints();

  n.printPossibles();

  return 0;
}
