#include <iostream>
#include "PrintJob.h"
#include "Heap.h"

using namespace std;

Heap::Heap() : numItems(0){
  arr[0] = nullptr;
}

void Heap::enqueue (PrintJob* newJob) {
  // If more than max number, then throw an error
  if (numItems >= MAX_HEAP_SIZE) throw runtime_error("Overflow");
  // Increase number of items, insert into array, then move up the array depending on priority
  numItems++;
  arr[numItems-1] = newJob;
  moveUp(numItems-1);
  return;
}

void Heap::dequeue() {
  // If less than max number, then throw an error
  if (numItems == 0) throw runtime_error("Underflow");
  // Move last item to the front of the heap, then move down the queue depending on priority
  arr[0] = arr[numItems-1];
  numItems--;
  trickleDown(0);
  return;
}

PrintJob* Heap::highest() const {
  // Throw error if heap is empty
  if (numItems == 0) throw runtime_error("Heap is empty");
  return (arr[0]);
}


void Heap::print() const {
  // Throw error if heap is empty
  if (numItems == 0) throw runtime_error("Heap is empty");
  PrintJob* highestJob = highest();
  // Get the highest node and output it's data in the proper format
  cout << "Priority: " << highestJob->getPriority() << ", ";
  cout << "Job Number: " << highestJob->getJobNumber() << ", ";
  cout << "Number of Pages: " << highestJob->getPages() << endl;
}


// Helper function used to dequeue things and fix the array
void Heap::trickleDown(int index) {
  // If index > 3 then no need to trickle down
  if (index > 3) return;

  // Get left/ri\ght indices
  int leftIndex = (index * 2) + 1;
  int rightIndex = (index * 2) + 2;

  // If more items than both indexes
  if ((numItems > leftIndex) && (numItems > rightIndex)) {
    // If job at index has lower priority than either left/right
    if ((arr[index]->getPriority() < arr[leftIndex]->getPriority()) || (arr[index]->getPriority() < arr[rightIndex]->getPriority())) {
      // Replace with the job with larger priority and then recursively call trickle to fix remaining array
      if (arr[leftIndex]->getPriority() > arr[rightIndex]->getPriority()) {
        swap(arr[index], arr[leftIndex]);
        trickleDown(leftIndex);
      }
      else {
        swap(arr[index],arr[rightIndex]);
        trickleDown(rightIndex);
      }
    }
  }
  // Simply swap if only greater than left index
  else if (numItems > leftIndex) {
    swap(arr[index], arr[rightIndex]);
  }
}

// Helper function used to queue things into the heap
void Heap::moveUp(int index) {
    // If index is zero then nothing to move up
    if (index == 0) return;
    // If priority is less than the one above it (found by doing index-1/2) then swap the to
    else if (arr[(index - 1)/2]->getPriority() < arr[index]->getPriority()) {
        swap(arr[index], arr[(index - 1)/2]);
        // Recursively call move up on the remaining ones
        moveUp((index - 1)/2);
    }
    else return;
}
