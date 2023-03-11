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
