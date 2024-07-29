#include "Tree.h"
#include <iostream>

using namespace std;

#define A "A"
#define B "B"
#define C "C"
#define D "D"
#define E "E"
#define F "F"
#define G "G"
#define H "H"
#define I "I"
#define J "J"
#define K "K"
#define L "L"
#define M "M"
#define N "N"
#define O "O"
#define P "P"
#define Q "Q"
#define R "R"

void printOrders(Tree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << "Inorder = ";
  tree->inOrder( );
  cout << "Postorder = ";
  tree->postOrder( );
}

int main( ) {

  Tree tree;


  //------------------------------------------------------------------------
  // Test simple inserting from page 1
  cout << "Test 1" << endl;
  tree.insert(C);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 2" << endl;
  tree.insert(O);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 3" << endl;
  tree.insert(G);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 4" << endl;
  tree.insert(K);
  tree.insert(P);
  printOrders(&tree);
  
  cout << "----------------------------------------------------" << endl;
  cout << "Test 5" << endl;
  tree.insert(N);
  tree.insert(E);
  
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 6" << endl;
  tree.insert(I);
  printOrders(&tree);
  cout << "----------------------------------------------------" << endl;
  cout << "Test 7" << endl;
  if (!tree.search(C) 
      || !tree.search(O) 
      || !tree.search(G) 
      || !tree.search(K) 
      || !tree.search(P) 
      || !tree.search(N)
      || !tree.search(E) 
      || !tree.search(I) 
      || tree.search("z")) {
    cout << "Seach phase failed" << endl;
  } else {
    cout << "Search phase passed" << endl;
  }
  cout << "----------------------------------------------------" << endl;
// Test simple inserting and removing from pages 1b and 2b
  Tree tree2;
  cout << "Test 8" << endl;
  tree2.remove(C);
  printOrders(&tree2);
  tree2.insert(C);
  tree2.remove(C);
  printOrders(&tree2);
  tree2.insert(C);
  tree2.insert(O);
  tree2.remove(O);
  printOrders(&tree2);
  cout << "----------------------------------------------------" << endl;
  
  return 0;
}
