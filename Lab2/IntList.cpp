#include "IntList.h"
#include <iostream>
using namespace std;

ostream & operator<<(ostream &out, const IntList &rhs) {
      // If empty nothing to insert into the ostream
      if (rhs.empty()) {
        return out;
      }
      else {
        // Use curr to output the first node's data
        IntNode* curr = rhs.dummyHead.next;
        out << curr->data;
        curr = curr->next;
        // Use while loop to keep outputing data with preceding space until curr points to dummyTail
        while (curr != &rhs.dummyTail) {
            out << " " << curr->data;
            curr = curr->next;
        }
        return out;
      }
}

IntList::~IntList() {
  // Uses pop_front to continuously delete nodes until the list is empty
  while (!empty()) {
    pop_front();
  }
}

void IntList::push_front(int value) {
  // Create the new node
  IntNode* newNode = new IntNode(value);

  if (empty()) {
    dummyHead.next = newNode;
    newNode->prev = &dummyHead;
    newNode->next = &dummyTail;
    dummyTail.prev = newNode;
  }
  // If list is not empty handle the push front differently
  else {
    (dummyHead.next)->prev = newNode;
    newNode->next = dummyHead.next;
    dummyHead.next = newNode;
    newNode->prev = &dummyHead; 
  }
}

void IntList::pop_front() {
  // If list is empty can just return since nothing to pop
  if (empty()) {
    return;
  }
  // If 1 element in list then dummyhead and dummytail will point to each other after pop
  else if (dummyHead.next == dummyTail.prev) {
    IntNode* victimNode = dummyHead.next;
    dummyHead.next = &dummyTail;
    dummyTail.prev = &dummyHead;
    delete victimNode;
  }
// If more than 1 element then adjust adjacent nodes then use temp to delete the 1st node
  else {
    IntNode* victimNode = dummyHead.next;
    dummyHead.next = victimNode->next;
    (victimNode->next)->prev = &dummyHead;
    delete victimNode;
  }
}

void IntList::push_back(int value) {
  // Create the new node
  IntNode* newNode = new IntNode(value);

  if (empty()) {
    dummyHead.next = newNode;
    newNode->prev = &dummyHead;
    newNode->next = &dummyTail;
    dummyTail.prev = newNode;
  }
   // If list is not empty then handle the push back differently
  else {
    (dummyTail.prev)->next = newNode;
    newNode->prev = dummyTail.prev;
    dummyTail.prev = newNode;
    newNode->next = &dummyTail;
  }
}

void IntList::pop_back() {
  // If list is empty can just return since nothing to pop
  if (empty()) {
    return;
  }
  // If 1 element in list then dummyhead and dummytail will point to each other after pop
  else if (dummyHead.next == dummyTail.prev) {
    IntNode* victimNode = dummyTail.prev;
    dummyHead.next = &dummyTail;
    dummyTail.prev = &dummyHead;
    delete victimNode;
  }
  // If more than 1 element then adjust adjacent nodes then use temp to delete the last node
  else {
    IntNode* victimNode = dummyTail.prev;
    (victimNode->prev)->next = &dummyTail;
    dummyTail.prev = victimNode->prev;
    delete victimNode;
  }
}

bool IntList::empty() const {
  return (dummyHead.next == &dummyTail) and (dummyTail.prev == &dummyHead);
}

void IntList::printReverse() const {
  // If empty then nothing to insert into cout
  if (empty()) {
        return;
      }
  else {
    // Use curr to output the last node's data
    IntNode* curr = dummyTail.prev;
    cout << curr->data;
    curr = curr->prev;
    // Use while loop to keep outputing data with preceding space until curr points to dummyHead
    while (curr != &dummyHead) {
        cout << " " << curr->data;
        curr = curr->prev;
    }
  }
}

