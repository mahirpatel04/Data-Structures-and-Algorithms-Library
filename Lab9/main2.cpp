#include <string>
#include <iostream>
#include <ctime>
using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds
const int NUMBERS_SIZE = 50000;

void InsertionSort(int numbers[], int numbersSize)  
{
    int i = 0;
    int j = 0;
    int tempValue = 0;
    for (i = 1; i < numbersSize; ++i)
    {
        j = i;
        while (j > 0 && numbers[j] < numbers[j - 1])
        {
            tempValue = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = tempValue;
            j = j - 1;
        }
    }
}

int Partition_midpoint(int numbers[], int i, int k)
{
    int midPoint = (i + k) / 2;
    int pivot = numbers[midPoint];
    bool done = false;
    while (!done)
    {
        while (numbers[i] < pivot)
        {
            i = i + 1;
        }
        while (numbers[k] > pivot)
        {
            k = k - 1;
        }
        if (i >= k)
        {
            done = true;
        }
        else
        {
            int tempValue = numbers[i];
            numbers[i] = numbers[k];
            numbers[k] = tempValue;
            i = i + 1;
            k = k - 1;
        }
    }
    return k;
}

int Partition_medianOfThree(int numbers[], int i, int k)
{   int pivot;          
    int arr[3];                 //creates an array with the first, last and middle elemnt
    arr[0]= numbers[i];
    arr[1]=numbers[(i+k)/2];
    arr[2]=numbers[k];
    InsertionSort(arr, 3);     //uses insertion sort to dfind the median 
    pivot=arr[1];
    bool done = false;
    while (!done)
    {
        while (numbers[i] < pivot)
        {
            i = i + 1;
        }
        while (numbers[k] > pivot)
        {
            k = k - 1;
        }
        if (i >= k)
        {
            done = true;
        }
        else
        {
            int tempValue = numbers[i];
            numbers[i] = numbers[k];
            numbers[k] = tempValue;
            i = i + 1;
            k = k - 1;
        }
    }
    return k;
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    if (i >= k)
    {
        return;
    }
    int lowEndIndex = Partition_midpoint(numbers, i, k);
    Quicksort_midpoint(numbers, i, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    if (i >= k)
    {
        return;
    }
    int lowEndIndex = Partition_medianOfThree(numbers, i, k);
    Quicksort_medianOfThree(numbers, i, lowEndIndex);
    Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}



int genRandInt(int low, int high)
{
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[])
{
    for (int i = 0; i < NUMBERS_SIZE; ++i)
    {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int main(){   
    int insertion[NUMBERS_SIZE];
    int midpoint[NUMBERS_SIZE];
    int median[NUMBERS_SIZE];

    fillArrays(insertion, midpoint, median);
    clock_t Start = clock();
    InsertionSort(insertion, NUMBERS_SIZE - 1);

    clock_t End = clock();
    int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "time for insertion sort is: " << elapsedTime << endl;
    Start = clock();
    Quicksort_midpoint(midpoint, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "time for Quicksort_midpoint sort is: " << elapsedTime << endl;
    Start = clock();
    Quicksort_medianOfThree(median, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "time for Quicksort_medianOfThree sort is: " << elapsedTime << endl;
    return 0;
}