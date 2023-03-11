#include <bits/stdc++.h>
using namespace std;

void quickSort(float a[], int l, int r)
{
    float p = a[(l + r) / 2]; // Chọn pivot là phần tử giữa
    int i = l, j = r;         // Khai báo hai biến chạy để duyệt mảng
    while (i < j)
    {
        while (a[i] < p) // Bỏ qua các phần tử nhỏ hơn pivot và nằm bên trái
            i++;
        while (a[j] > p) // Bỏ qua các phần tử lớn hơn pivot và nằm bên phải
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]); // Thay đổi vị trí 2 phần từ nằm khác bên
            i++;
            j--;
        }
    }
    // Chia thành 2 nửa để sắp xếp
    if (i < r)
        quickSort(a, i, r);
    if (l < j)
        quickSort(a, l, j);
}

void merge(float arr[], int const left, int const mid, int const right)
{
    auto const subArrOne = mid - left + 1;
    auto const subArrTwo = right - mid;

    // Tạo mảng tạm
    auto *leftarr = new int[subArrOne],
         *rightarr = new int[subArrTwo];

    // Sao chép dữ liệu vào mảng trái và phải
    for (auto i = 0; i < subArrOne; i++)
        leftarr[i] = arr[left + i];
    for (auto j = 0; j < subArrTwo; j++)
        rightarr[j] = arr[mid + 1 + j];

    auto indexOfsubArrOne = 0, indexOfsubArrTwo = 0, indexOfMergedarr = left; // Khai báo chỉ số của các mảng

    // Gộp 2 mảng con về mảng cha
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
    // Gán mảng con trái về lại mảng cha
    while (indexOfsubArrOne < subArrOne)
    {
        arr[indexOfMergedarr] = leftarr[indexOfsubArrOne];
        indexOfsubArrOne++;
        indexOfMergedarr++;
    }
    // Gán mảng con phải về lại mảng cha
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

void heapify(float arr[], int n, int i)
{
    int max = i;                    // Lưu vị trí đỉnh max ban đầu
    int l = i * 2 + 1;              // Vị trí con trái
    int r = l + 1;                  // Vị trí con phải
    if (l < n && arr[l] > arr[max]) // Nếu tồn tại con trái lớn hơn cha, gán max = L
        max = l;
    if (r < n && arr[r] > arr[max]) // Nếu tồn tại con phải lớn hơn arr[max], gán max = r
        max = r;
    if (max != i)
    {                           // Nếu max != i, tức là cha không phải lớn nhất
        swap(arr[i], arr[max]); // Đổi chỗ cho phần tử lớn nhất làm cha
        heapify(arr, n, max);   // Đệ quy vun các node phía dưới
    }
}

// Ham sap xep vun dong
void heapSort(float arr[], int n)
{
    // vun dong tu duoi len len de thanh heap
    for (int i = n / 2 - 1; i >= 0; i--) // i chạy từ n/2 - 1 về 0 sẽ có n/2 đỉnh
        heapify(arr, n, i);              // Vun từng đỉnh
    // Vòng lặp để thực hiện vun đống và lấy phần tử
    for (int j = n - 1; j > 0; j--)
    {                         // chạy hết j == 1 sẽ dừng; mỗi lần j - 1, tương đương với k xét phần tử cuối
        swap(arr[0], arr[j]); // đổi chỗ phần tử lớn nhất
        heapify(arr, j, 0);   // vun lại đống,
    }
}

float a[1000005];

int main()
{
    auto start = chrono::high_resolution_clock::now(); // start the timer

    // code sort của ông
    ifstream fi("test10.txt");
    ofstream fo("ans1.txt");
    for (int i = 0; i < 1e6; i++)
        fi >> a[i];
    mergeSort(a, 0, 1000000 - 1);
    for (int i = 0; i < 1e6; i++)
        fo << a[i];
    auto end = chrono::high_resolution_clock::now();                            // end the timer
    auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start); // calculate the time taken
    cout << "Time taken by code segment: " << time_taken.count() << " milliseconds." << endl;
    // return 0;
}
