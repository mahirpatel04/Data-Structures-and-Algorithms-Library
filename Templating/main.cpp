#include <exception>
#include <iostream>
#include <vector>

using namespace std;

// Creates vector
vector<char> createVector() {
  int vecSize = rand() % 26;
  char c = 'a';
  vector<char> vals;
  for(int i = 0; i < vecSize; i++)
    {
      vals.push_back(c);
      c++;
    }
  return vals;
}

// Creates a function template that finds the index for the minimum value in a vector starting from a certain index passed in
template<typename T> 
unsigned min_index(const vector<T> &vals, unsigned index) {

  // We don't need to throw if index is out of range because we ensure index is a valid input in the main function
  unsigned int lowestIndex = index;
  // Iterates through the list and updates lowestIndex is lesser value is found
  for (unsigned int i = index + 1; i < vals.size(); i++) {
    if (vals.at(i) < vals.at(lowestIndex)) {
      lowestIndex = i;
    }
  }
  return lowestIndex;
}
// Creates a function template that uses Selection Sort to sort a vector of type T objects
template<typename T> 
void selection_sort(vector<T> &vals) {
  // Edge case where the vector is small
  if (vals.size() <= 1) {
    return;
  }
  // Iterate through the list, find the minimum value, swap positions of minimum value with first element of unsorted part of the list
  for (unsigned int i = 0; i < vals.size()-1; i++) {
    unsigned int lowest = min_index(vals, i);
    T temp = vals.at(i);
    vals.at(i) = vals.at(lowest);
    vals.at(lowest) = temp;
  }
}
// Simply returns the item at a certain index. The .at() used because it has automatic range checking
template<typename T> 
T getElement(const vector<T>& vals, int index) {
  if ((index < 0) or (index > vals.size())) {
        throw out_of_range("out of range exception occured");
      }
  return vals[index];
}

int main() {
  srand(time(0));
  vector<char> vals = createVector();
  int numOfRuns = 10;
  
  while(--numOfRuns >= 0){
    cout << "Enter a number: " << endl;
    int index;
    if (not (cin >> index)) {
      throw runtime_error("could not read the index");
    }
    // Try to get the element at the specified index
    try {
      // If index is out of range then throw
      char curChar = getElement(vals,index);
      cout << "Element located at " << index << ": is " << curChar << endl;
    }
    catch(out_of_range& excpt) {
      cout << excpt.what() << endl;
    }
  }
  cout << endl;

  
  // TESTING SELECTION SORT
  vector<int> intVec;
  // Testing empty vector passed into selection sort
  selection_sort(intVec);
  cout << "Original list is empty" << endl;
  cout << "Expected: " << endl;
  cout << "Actual: ";
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  cout << endl << endl;

  // Testing vector size = 1 passed into selection sort
  intVec.push_back(1);
  cout << "Original: " ;
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  cout << endl;
  cout << "Expected: 1" << endl;
  cout << "Actual: ";
  selection_sort(intVec);
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  cout << endl << endl;
  
  // Testing vector size = 2 passed into selection sort
  intVec.push_back(-1);
  cout << "Original: " ;
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  cout << endl;
  cout << "Expected: -1 1" << endl;
  cout << "Actual: ";
  selection_sort(intVec);
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  cout << endl << endl;

  // Testing vector size = 10 passed into selection sort
  intVec.push_back(10);
  intVec.push_back(-1000);
  intVec.push_back(0);
  intVec.push_back(-200);
  intVec.push_back(200);
  intVec.push_back(400);
  intVec.push_back(0);
  intVec.push_back(-2000);
  cout << "Original: " ;
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  cout << endl;
  cout << "Expected: -2000 -1000 -200 -1 0 0 1 3 10 200 400" << endl;
  cout << "Actual: ";
  selection_sort(intVec);
  for (unsigned int i = 0; i < intVec.size(); i++) {
    cout << intVec.at(i) << " ";
  }
  
  return 0;
}
