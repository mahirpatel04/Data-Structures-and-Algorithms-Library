#pragma once

#include <stdexcept>

using std::overflow_error;
using std::runtime_error;
using std::underflow_error;

// Max size of the stack is 20
#define MAX_SIZE (20)

template<typename T>
class stack {
  private:
    // Create the array storing type T objects with MAX_SIZE
    T arr[MAX_SIZE];
    // Size of the stack
    int stackSize = 0;
  public:
    // Inserts a new element of type T into the data.
    // If the data array is full, throws an overflow_error
    void push(const T& value) {
      if (stackSize == MAX_SIZE) {
        throw overflow_error("Called push on full stack.");
      }
      arr[stackSize++] = value;
    }

    // Returns true if the stack is empty otherwise it returns false.
    bool empty() const {
      return (stackSize == 0);
    }

    // Removes the last element from data. 
    // If the data array is empty, throws an underflow_error
    void pop() {
      if (empty()) {
        throw underflow_error("Called pop on empty stack.");
      }
      --stackSize;
    }

    // Removes the last two elements from data.
    // If the data array is empty or size 1, throws appropriate underflow error
    void pop_two() {
      if (empty()) {
        throw underflow_error("Called pop_two on empty stack.");
      }
      else if (stackSize == 1) {
        throw underflow_error("Called pop_two on a stack of size 1.");
      }
      stackSize -= 2;
    }

    // Returns the top element of stack. If stack is empty, throws an underflow_error
    // Non-const version
    T& top() {
      if (empty()) {
        throw underflow_error("Called top on empty stack.");
      }
      else {
        return arr[stackSize-1];
      }
    }
    // Const version
    const T& top() const {
      if (empty()) {
        throw underflow_error("Called top on empty stack.");
      }
      else {
        return arr[stackSize-1];
      }
    }
  };
