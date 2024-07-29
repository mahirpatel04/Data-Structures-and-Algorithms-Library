#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include <algorithm>
using std::cout;
using std::endl;
using std::sort;

// Clock to keep track of runtimes
using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;

// Randome integer
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// Fill 3 different arrays
void fillArrays(int arr1[], int arr2[],int arr3[]) {
  for(int i = 0; i < NUMBERS_SIZE; ++i){
    arr1[i] = genRandInt(0,NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

// Parititioning for Quicksort with midpoint
int Partition_midpoint(int numbers[], int low, int high) {
  // Get midpoint and set the pivot
  int midpoint = low + (high - low) / 2;
  int pivot = numbers[midpoint];
  // While the partitioning isn't over keep swapping
  bool done = false;
  while (!done) {
    // If number is good then increse the low/high index
    while (numbers[low] < pivot) {
      low += 1;
    }
    while (pivot < numbers[high]) {
      high -= 1;
    }
    
    if (low >= high) {
      done = true;
    }
    // Swap numbers if they need to be swapped
    else {
      int temp = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = temp;
      low += 1;
      high -= 1;
    }
  }
  return high;
}

void InsertionSort(int numbers[], int numbersSize) {
  int i = 0;
  int j = 0;
  // For-loop for every element in the array
  for (i = 1; i < numbersSize; ++i) {
    j = i;
    // For every element within the array that is bigger than the target one swap them
    while (j > 0 && numbers[j] < numbers[j - 1]) {
      int temp = numbers[j];
      numbers[j] = numbers[j - 1];
      numbers[j - 1] = temp;
      --j;
      }
   }
}

int Partition_medianOfThree(int numbers[], int low, int high) {
  int pivot;
  // Create an array, put in the three values, sort it, then find the median       
  int arr[3];
  arr[0]= numbers[low];
  arr[1]=numbers[(low + high) / 2];
  arr[2]=numbers[high];
  InsertionSort(arr, 3);
  // The median becomes the pivot
  pivot=arr[1];
  // Same as partition_midpoint keep swapping as long as low and high don't meet
  bool done = false;
  while (!done) {
    // Move low up if current value is less than pivot
    while (numbers[low] < pivot) {
      low = low + 1;
    }
    // Move high down if current value is greater than pivot
    while (numbers[high] > pivot) {
      high = high - 1;
    }
    if (low >= high) {
      done = true;
    }
    else {
      // Perform the swap
      int tempValue = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = tempValue;
      low = low + 1;
      high = high - 1;
      }
    }
    // Return the higher index
    return high;
}


void Quicksort_midpoint(int numbers[], int low, int high) {
  // If low and high have met then simply return
  if (low >= high) {
      return;
  }
  // Get the middle index and partition the array
  int lowEndIndex = Partition_midpoint(numbers, low, high);
  // Recursively sort/partition the sub-arrays as well
  Quicksort_midpoint(numbers, low, lowEndIndex);
  Quicksort_midpoint(numbers, lowEndIndex + 1, high);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
  if (i >= k) return;
  // Make the partitions by finding the lowEndIndex
  int lowEndIndex = Partition_medianOfThree(numbers, i, k);
  // Recursively sort both partitions
  Quicksort_medianOfThree(numbers, i, lowEndIndex);
  Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}

static bool is_sorted(int numbers[], int numbersSize) {
  // Function to quickly check if an array is sorted
  if (numbersSize <= 0) return true;
  int last = numbers[0];
  // For every value check that the next one is greater
  for(int i=0; i < numbersSize; ++i) {
    int curr = numbers[i];
    if (curr < last) return false;
    last = curr;
  }
  return true;
}

static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for(int i=0;i<static_cast<int>(source.size()); ++i) {
    array[i] = source[i];
  }
}
int main() {
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for(int i=0; i<4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    // BUBBLE SORT
    {
      copy_vector_into_array(sample, test_array);
      // Time counting
      clock_t Start = clock();
      BubbleSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      // Output the elapsed time
      cout << elapsedTime << " ms for bubble sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // MERGE SORT
    {
      copy_vector_into_array(sample, test_array);
      // Time counting
      clock_t Start = clock();
      MergeSort(test_array, 0, size-1);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      cout << elapsedTime << " ms for merge sort " << endl;
      // Output the elapsed time
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // RADIX SORT
    {
      copy_vector_into_array(sample, test_array);
      // Time counting
      clock_t Start = clock();
      RadixSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start)/CLOCKS_PER_MS;
      // Output the elapsed time
      cout << elapsedTime << " ms for radix sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
  }
 
  return 0;
}

static void BubbleSort(int numbers[], int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (numbers[j] > numbers[j + 1]) {
	std::swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

static void merge(int numbers[], int start, int mid, int end) {
  int start2 = mid + 1;
 
  // If the direct merge is already sorted
  if (numbers[mid] <= numbers[start2]) {
    return;
  }
 
  // Two pointers to maintain start of both sub-arrays to merge
  while (start <= mid && start2 <= end) {
 
    // If element 1 is in right place
    if (numbers[start] <= numbers[start2]) {
      start++;
    } else {
      int value = numbers[start2];
      int index = start2;
 
      // Shift all the elements between element 1
      // element 2, right by 1.
      while (index != start) {
	numbers[index] = numbers[index - 1];
	index--;
      }
      numbers[start] = value;
 
      // Update all the pointers
      start++;
      mid++;
      start2++;
    }
  }
}

static void MergeSort(int numbers[], int left, int right) {
  if (left < right) {
    int mid = (left + right)/2;
    // Recursively sort the left side and the right sides
    MergeSort(numbers, left, mid);
    MergeSort(numbers, mid+1, right);
    // Combine them
    merge(numbers, left, mid, right);
  }
}

static void RadixSort(int numbers[], int size) {
  int divisor = 1;
  bool more = true;
  for(int pass=0; more ; pass++) {
    // Make 10 large buckets
    std::vector< std::vector<int> > buckets(10);
    // For each bucket reserve a set number of spots
    for(int i=0;i<10;++i) buckets[i].reserve(NUMBERS_SIZE);
    more = false;
    for(int i=0; i<size; ++i) {
      // Put into the buckets
      int digit = (numbers[i]/divisor)%10;
      if (numbers[i]/divisor/10 > 0) more = true;
      buckets[digit].push_back(numbers[i]);
    }
    divisor *= 10;
    int index = 0;
    for(int i=0; i<10; ++i) {
      // Combine the buckets
      const std::vector<int>& bucket = buckets[i];
      for(int j=0; j<static_cast<int>(bucket.size()); ++j) {
	numbers[index++] = bucket[j];
      }
    }
  }
}
