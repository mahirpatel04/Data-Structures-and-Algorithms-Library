#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(const string& payload) {
    // Creates new node with payload and next node to be nullptr
    Node* new_node;
    new_node = new Node();
    new_node->payload = payload;
    new_node->next = nullptr;
    return new_node;
}

Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;
    // For loop to load the game until there are n players in the list
    for (int i = 0; i < n; ++i) {
        name = names.at(i);
	    // Edge case: List is initially empty
        if (head == nullptr) {
            head = newNode(name);
            prev = head;
        }
        else {
            prev->next = newNode(name);
            prev = prev->next;
        }
    }
    // Makes the list circular
    prev->next = head;

    return head;
}

void print(const Node* start) {
  const Node* curr = start;
  // Checking if curr is nullptr since it helps check that the circular list 
  // isn't broken before curr reaches the starting player
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break; // exit circular list
    }
  }
}

Node* runGame(Node* start, int k) {
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing points to themselves
        if (k==1) {
          curr = curr->next;
        } 
        else {
          for (int i = 1; i < k; ++i) { // finds the kth node
            prev = prev->next;
            curr = prev->next;
          }
        }
        // deletes the kth node
        prev->next = curr->next;
        delete curr;
        prev = prev->next;
        curr = prev;
    }

    return curr; // last person standing
}

// Driver program to test above functions
int main() {
    int n=1, k=1;
    string name;
    vector<string> names;

    // Gets Inputs
    cin >> n >> k;
    if (!cin) throw runtime_error("error reading n and k from input");
    
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // Initialize and run the game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);
  
    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    delete lastPerson;

    return 0;
}

