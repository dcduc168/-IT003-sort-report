#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

void merge(float arr[], int const left, int const mid, int const right)
{
    auto const subArrOne = mid - left + 1;
    auto const subArrTwo = right - mid;

    auto *leftarr = new int[subArrOne],
         *rightarr = new int[subArrTwo];

    for (auto i = 0; i < subArrOne; i++)
        leftarr[i] = arr[left + i];
    for (auto j = 0; j < subArrTwo; j++)
        rightarr[j] = arr[mid + 1 + j];

    auto indexOfsubArrOne = 0, indexOfsubArrTwo = 0, indexOfMergedarr = left;

    while (indexOfsubArrOne < subArrOne && indexOfsubArrTwo < subArrTwo)
    {
        if (leftarr[indexOfsubArrOne] <= rightarr[indexOfsubArrTwo])
        {
            arr[indexOfMergedarr] = leftarr[indexOfsubArrOne];
            indexOfsubArrOne++;
        }
        else
        {
            arr[indexOfMergedarr] = rightarr[indexOfsubArrTwo];
            indexOfsubArrTwo++;
        }
        indexOfMergedarr++;
    }

    while (indexOfsubArrOne < subArrOne)
    {
        arr[indexOfMergedarr] = leftarr[indexOfsubArrOne];
        indexOfsubArrOne++;
        indexOfMergedarr++;
    }

    while (indexOfsubArrTwo < subArrTwo)
    {
        arr[indexOfMergedarr] = rightarr[indexOfsubArrTwo];
        indexOfsubArrTwo++;
        indexOfMergedarr++;
    }
    delete[] leftarr;
    delete[] rightarr;
}

void mergeSort(float arr[], int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

float a[1000000];

int main()
{
    auto start = high_resolution_clock::now();
    ifstream fi("test.txt");
    ofstream fo("ans.txt");
    for (int i = 0; i < 1e6; i++)
        fi >> a[i];
    mergeSort(a, 0, 1000000 - 1);
    for (int i = 0; i < 1e6; i++)
        fo << a[i];
    auto end = high_resolution_clock::now();
    auto time_taken = duration_cast<milliseconds>(end - start);
    cout << "Time taken by code segment: " << time_taken.count() << " milliseconds." << endl;
    return 0;
}
