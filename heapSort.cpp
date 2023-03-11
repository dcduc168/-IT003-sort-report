#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

void heapify(float arr[], int n, int i)
{
    int max = i;
    int l = i * 2 + 1;
    int r = l + 1;
    if (l < n && arr[l] > arr[max])
        max = l;
    if (r < n && arr[r] > arr[max])
        max = r;
    if (max != i)
    {
        swap(arr[i], arr[max]);
        heapify(arr, n, max);
    }
}

void heapSort(float arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int j = n - 1; j > 0; j--)
    {
        swap(arr[0], arr[j]);
        heapify(arr, j, 0);
    }
}

float a[1000000];

int main()
{
    auto start = high_resolution_clock::now();
    ifstream fi("test.txt");
    ofstream fo("ans.txt");
    for (int i = 0; i < 1e6; i++)
        fi >> a[i];
    heapSort(a, 1000000 - 1);
    for (int i = 0; i < 1e6; i++)
        fo << a[i];
    auto end = high_resolution_clock::now();
    auto time_taken = duration_cast<milliseconds>(end - start);
    cout << "Time taken by code segment: " << time_taken.count() << " milliseconds." << endl;
    return 0;
}
