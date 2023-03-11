#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

void quickSort(float a[], int l, int r)
{
    float p = a[(l + r) / 2];
    int i = l, j = r;
    while (i < j)
    {
        while (a[i] < p)
            i++;
        while (a[j] > p)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (i < r)
        quickSort(a, i, r);
    if (l < j)
        quickSort(a, l, j);
}

float a[1000000];

int main()
{
    auto start = high_resolution_clock::now();
    ifstream fi("test.txt");
    ofstream fo("ans.txt");
    for (int i = 0; i < 1e6; i++)
        fi >> a[i];
    quickSort(a, 0, 1000000 - 1);
    for (int i = 0; i < 1e6; i++)
        fo << a[i];
    auto end = high_resolution_clock::now();
    auto time_taken = duration_cast<milliseconds>(end - start);
    cout << "Time taken by code segment: " << time_taken.count() << " milliseconds." << endl;
    return 0;
}
