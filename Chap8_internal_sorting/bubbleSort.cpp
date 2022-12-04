#include <iostream>
#include "C:\Users\19735\Desktop\SJJG\Chap2_linear_list/List/List.h"
using namespace std;

void bubbleSort(List<int> arr)
{
    cout << "before sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;

    for (int i = 0; i < arr.getLen() - 1; i++)
    {
        bool flag = 0; //用来标识是否进行过交换
        for (int j = i + 1; j < arr.getLen(); j++)
        {
            if (arr[i] > arr[j])
            {
                flag = 1;
                arr[i] = arr[i] ^ arr[j];
                arr[j] = arr[i] ^ arr[j];
                arr[i] = arr[i] ^ arr[j];
            }
        }

        if (flag == 0)
        {
            break;
        }
    }

    cout << "after sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
}

int main()
{
    int a[10] = {1, 2, 3, 4, 5};
    List<int> arr(5, a);

    bubbleSort(arr);
}