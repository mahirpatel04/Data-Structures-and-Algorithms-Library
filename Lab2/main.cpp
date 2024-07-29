#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
  IntList list;
  
  cout << "empty: " << list << endl;
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  list.pop_back();
  cout << "pop back: " << list << endl;
  list.pop_front();
  cout << "pop front: " << list << endl;

  // Multiple newlines so I can see better...
  cout << endl;
  cout << endl;
  cout << endl;

  // Testing printReverse and destructor
  IntList* listTwo = new IntList();
  listTwo->push_back(1);
  listTwo->push_back(2);
  listTwo->push_back(3);
  cout << "Normal direction: " << listTwo << endl << "Reverse direction: ";
  listTwo->printReverse();
  cout << endl;   
  delete listTwo;
  
  return 0;
}
