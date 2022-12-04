#include <iostream>
using namespace std;
#include "C:\Users\19735\Desktop\SJJG\Chap2_linear_list/List/List.h"

void selectSort(List<int> arr)
{
    cout << "before sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
    int len = arr.getLen();
    for (int i = 0; i < len - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] > arr[max])
            {
                max = j;
            }
        }
        if (max != i)
        {
            arr[i] = arr[i] ^ arr[max];
            arr[max] = arr[i] ^ arr[max];
            arr[i] = arr[i] ^ arr[max];
        }
    }
    cout << "after sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
}

int main()
{
    int a[10] = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    List<int> arr(10, a);
    selectSort(arr);
}