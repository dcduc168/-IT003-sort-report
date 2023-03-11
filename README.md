# IT003.N21.CTTN_sortAlgorithm

# Báo cáo thực nghiệm các thuật toán sắp xếp

> **Họ và tên**: Đinh Công Đức <br>
> **MSSV**: 22520262 <br>
> **Lớp**: ATTN2022 <br>

## Mục lục
- [Đề bài](#đề-bài)
- [Tạo bộ dữ liệu](#tạo-bộ-dữ-liệu)
- [Các thuật toán sắp xếp](#các-thuật-toán-sắp-xếp)
- [Quick sort](#quick-sort)
    - [Code cài đặt](#code-cài-đặt)
    - [Đánh giá](#đánh-giá)
- [Merge sort](#merge-sort)
    - [Code cài đặt](#code-cài-đặt-1)
    - [Đánh giá](#đánh-giá-1)
- [Heap sort](#heap-sort)
    - [Code cài đặt](#code-cài-đặt-2)
    - [Đánh giá](#đánh-giá-2)
- [Hàm sort của thư viện chuẩn STL (`std::sort`)](#hàm-sort-của-thư-viện-chuẩn-stl-stdsort)
    - [Code cài đặt](#code-cài-đặt-3)
- [Kết quả thử nghiệm](#kết-quả-thử-nghiệm)
    - [Bảng](#bảng)
    - [Biểu đồ](#biểu-đồ)


## Đề bài
- Tạo bộ dữ liệu gồm 10 dãy, mỗi dãy khoảng 1 triệu số thực (ngẫu nhiên); dãy thứ nhất đã có thứ tự tăng dần, dãy thứ hai có thứ tự giảm dần, 8 dãy còn lại trật tự ngẫu nhiên;
- Viết các chương trình sắp xếp dãy theo các thuật toán **QuickSort**, **HeapSort**, **MergeSort** và chương trình gọi **hàm sort** của C++;
- Chạy thử nghiệm mỗi chương trình đã viết ở trên với bộ dữ liệu đã tạo, ghi nhận thời gian thực thi từng lần thử nghiệm
- Viết báo cáo thử nghiệm: kết quả thử nghiệm ở dạng bảng dữ liệu và dạng biểu đồ; nhận xét kết quả thực nghiệm; báo cáo nộp bằng file PDF
- Toàn bộ các file liên quan cần được lưu trữ trên github (public) và ghi đường dẫn vào trong file báo cáo.

## Tạo bộ dữ liệu
Code tạo bộ dữ liệu gồm 1 triệu số thực ngẫu nhiên
```c++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Tạo dãy tăng dần và giảm dần
    vector<double> ascending_array(1000000);
    vector<double> descending_array(1000000);
    generate(ascending_array.begin(), ascending_array.end(), []()
             {
        static double current = 0.0;
        return current += 0.01; });
    reverse_copy(ascending_array.begin(), ascending_array.end(), descending_array.begin());

    // Tạo 8 dãy số ngẫu nhiên
    vector<vector<double>> random_arrays(8, vector<double>(1000000));
    for (int i = 0; i < 8; ++i)
    {
        generate(random_arrays[i].begin(), random_arrays[i].end(), rand);
    }

    // kết hợp tất cả các dãy số để tạo thành bộ dữ liệu cuối cùng
    vector<vector<double>> data;
    data.push_back(ascending_array);
    data.push_back(descending_array);
    for (int i = 0; i < 8; ++i)
    {
        data.push_back(random_arrays[i]);
    }

    // lưu bộ dữ liệu vào tệp
    ofstream fo("data.txt");
    for (const auto &array : data)
    {
        for (const auto &element : array)
        {
            fo << element << " ";
        }
        fo << endl;
    }
    fo.close();
    return 0;
}
```

## Các thuật toán sắp xếp
### Quick sort
#### Code cài đặt
```c++
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
```
#### Đánh giá
- Ưu điểm: Tốc độ sắp xếp nhanh
- Nhược điểm:
    - Phụ thuộc vào cách chọn phần tử chốt.
    - Không ổn định.


### Merge sort
#### Code cài đặt
```c++
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
```
#### Đánh giá
- Ưu điểm:
    - Chạy nhanh, độ phức tạp `O(NlogN)`
    - Ổn định
- Nhược điểm: Cần dùng thêm bộ nhớ để lưu mảng A.

### Heap sort
#### Code cài đặt
```c++
void heapify(int arr[], int n, int i)
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
void heapSort(int arr[], int n)
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
```
#### Đánh giá
- Ưu điểm:
    - Ít bị ảnh hưởng bởi dữ liệu đầu vào, có thể ứng dụng nhiều trong thực tế
    - Có độ phức tạp trung bình O (n log n) trong mọi trường hợp.
- Nhược điểm:
    - Là thuật toán sắp xếp không có tính ổn định
    - Không tối ưu trong mọi trường hợp

### Hàm sort của thư viện chuẩn STL (`std::sort`)
#### Code cài đặt
```c++
std::sort(a, a + n);
```


### Kết quả thử nghiệm
> Chạy trên máy cá nhân (AMD Ryzen 5 6600H) <br>
> Đơn vị tính thời gian mili giây (ms) <br>

#### Bảng
| Test |Quick sort|Merge sort|Heap sort|`std::sort`|
|:----:|:--------:|:--------:|:-------:|:---------:|
|1     |5830      |5283      |6069     |5637       |
|2     |5781      |5364      |5985     |5825       |
|3     |5020      |5194      |5203     |5018       |
|4     |5068      |5278      |5212     |4992       |
|5     |5078      |5204      |5223     |4954       |
|6     |5008      |5342      |5251     |5021       |
|7     |5195      |5211      |5291     |5074       |
|8     |5055      |5349      |5216     |5006       |
|9     |4992      |5303      |5265     |5011       |
|10    |5089      |5303      |5196     |5061       |

#### Biểu đồ
![Biểu đồ thời gian](https://i.ibb.co/c11TCvt/Bi-u-so-s-nh-th-i-gian-ch-y-c-c-thu-t-to-n-s-p-x-p-1.png)
