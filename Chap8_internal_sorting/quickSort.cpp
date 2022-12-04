#include <iostream>
#include "C:\Users\19735\Desktop\SJJG\Chap2_linear_list/List/List.h"
using namespace std;

void quickSort(int *arr, int left, int right)
{
    int l = left;
    int r = right;
    int pivot = arr[(l + r) / 2]; //中轴值
    int temp = 0;                 //临时变量,交换时使用

    while (l < r) // while循环的目的是让比pivor值小的放到边左边 大的放到右边
    {
        while (arr[l] < pivot) //在pivot的左边一直找 直到找到≥pivot的值才退出
        {
            l += 1;
        }

        while (arr[r] > pivot) //在pivot的右边一直找 直到找到≤pivot的值才退出
        {
            r -= 1;
        }
        //如果l==r说明pivot的左右两的值，已经按照左边全部是小于等于pivot的值，右边全部是大于等于pivot的值排列的了
        if (l >= r)
        {
            break;
        }

        temp = arr[l];
        arr[l] = arr[r];
        arr[r] = temp;

        //如果交换完后，发现arr[l]==pivot时 需要让r左移
        if (arr[l] == pivot)
        {
            r -= 1;
        }

        //如果交换完后，发现arr[l]==pivot时 需要让l右移
        if (arr[r] == pivot)
        {
            l += 1;
        }
    }

    //如果l==r 必须让l++ r-- 使二者错开 否则会出现栈溢出
    if (l == r)
    {
        l += 1;
        r -= 1;
    }

    //向左递归
    if (left < r)
    {
        quickSort(arr, left, r);
    }

    //向右递归
    if (right > l)
    {
        quickSort(arr, left, r);
    }
}

int main()
{
    int a[8] = {3, 99, 100, 5, -4, 8, 32, 0};
    List<int> arr(8, a);

    arr.Show();
    quickSort(a, 0, arr.getLen());

    // arr.Show();
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
}