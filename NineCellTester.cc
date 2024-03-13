#include <iostream>
#include <fstream>
#include "NineCell.hh"

int main(){

  ///////////////////////////////////////////////////
  // this program is for testing the NineCell class.
  // it directs std::cout to a file, which is compared to an example file within CMAKE
  ///////////////////////////////////////////////////

  std::ofstream out("NineCellTester.txt");
  std::streambuf *coutbuf  = std::cout.rdbuf(); // save cout buffer
  std::cout.rdbuf(out.rdbuf()); // redirect cout to 'out' file

  NineCell n;
  for(unsigned i=0; i<9; ++i){
    auto a = std::make_shared<Cell>(i);
    n.addCell(a);
  }

  // Test 1.
  std::cout << "Test 1. Check print function" << std::endl;
  n.printCellIDs();

  // Test 2.
  std::cout << std::endl << "Test 2. Try adding a 10th cell" << std::endl;
  auto a = std::make_shared<Cell>(9);
  n.addCell(a);

  // Test 3.
  std::cout << std::endl << " Test 3. Test 'print possibles' function" << std::endl;
  n.printPossibles();
  
  // Test 4.
  std::cout << std::endl << " Test 4. Set possibles for a cell" << std::endl;
  std::set<unsigned> valsA = {0,1,2};
  n.setPossibles(4, valsA);
  n.setPossibles(6, valsA);
  n.printPossibles();

  // Test 5.
  std::cout << std::endl << " Test 5. Test 'remove values' function" << std::endl;
  std::set<unsigned> valsB = {1,2,3};
  std::set<unsigned> indexes = {4,5,6};
  n.removeValues(valsB, indexes);
  n.printPossibles();
  
  // Test 6.
  std::cout << std::endl << " Test 6. 'resolve' function with elaborate example " << std::endl;

  // create a new NineCell object for this test
  NineCell n2;
  for(unsigned i=0; i<9; ++i){
    auto a = std::make_shared<Cell>(i);
    n2.addCell(a);
  }
  
  std::set<unsigned> poss;
  poss = {4,5};
  n2.setPossibles(0, poss);
  poss = {3};
  n2.setPossibles(1, poss);
  poss = {5,8};
  n2.setPossibles(2, poss);
  poss = {1,2,4,5,7,8};
  n2.setPossibles(3, poss);
  poss = {9};
  n2.setPossibles(4, poss);
  poss = {1,2};
  n2.setPossibles(5, poss);
  poss = {1,2,4,5,8};
  n2.setPossibles(6, poss);
  poss = {6};
  n2.setPossibles(7, poss);
  poss = {4,5,8};
  n2.setPossibles(8, poss);

  n2.printPossibles();
  n2.resolveConstraints();

  n2.printPossibles();
  n2.resolveConstraints();

  n2.printPossibles();

  ////////////////////////////////////////////////////

  // Test 7.
  std::cout << std::endl << " Test 7. 'resolve' function with simple " << std::endl;

  // create a new NineCell object for this test
  NineCell n3;
  for(unsigned i=0; i<9; ++i){
    auto a = std::make_shared<Cell>(i);
    n3.addCell(a);
  }

  poss = {6};
  n3.setPossibles(0, poss);
  poss = {1};
  n3.setPossibles(1, poss);
  poss = {9};
  n3.setPossibles(2, poss);
  poss = {8,9};
  n3.setPossibles(3, poss);
  poss = {5};
  n3.setPossibles(4, poss);
  poss = {7};
  n3.setPossibles(5, poss);
  poss = {4};
  n3.setPossibles(6, poss);
  poss = {3};
  n3.setPossibles(7, poss);
  poss = {2};
  n3.setPossibles(8, poss);

  std::cout << std::endl;
  n3.printPossibles();
  
  n3.resolveConstraints();

  std::cout << std::endl;
  n3.printPossibles();

  ////////////////////////////////////////////////////
  
  std::cout.rdbuf(coutbuf);
  out.close();

  return 0;
}
