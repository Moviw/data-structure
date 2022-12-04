#include <iostream>
using namespace std;
#include "C:\Users\19735\Desktop\SJJG\Chap2_linear_list/List/List.h"
#include "insertSort.cpp"

//缩小增量排序:希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序：随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止
void shellSort(List<int> &arr) //这种是移位式 运行速度较慢 甚至比插入排序还蛮
{
    cout << "before sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
    int len = arr.getLen();
    while (len != 1)
    {
        len /= 2;
        for (int i = len; i < arr.getLen(); i++)
        {
            for (int j = i - len; j >= 0; j -= len)
            {
                if (arr[j] < arr[j + len])
                {
                    arr[j] = arr[j] ^ arr[j + len];
                    arr[j + len] = arr[j] ^ arr[j + len];
                    arr[j] = arr[j] ^ arr[j + len];
                }
            }
        }
    }

    cout << "after sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
}

void shellSortEnhanced(List<int> &arr) //这种是移位式 运行速度变快了
{
    cout << "before sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
    int len = arr.getLen();
    while (len != 1)
    {
        len /= 2;
        for (int i = len; i < arr.getLen(); i++)
        {
            int j = i;
            int temp = arr[j];
            if (arr[j] < arr[i - len]) // 这里的if用于优化 如果不满足直接不进入while
            {
                while (j - len >= 0 && temp < arr[j - len])
                {
                    //移动
                    arr[j] = arr[j - len];
                    j -= len;
                }
                //当退出while后,就给temp找到插入的位置
                arr[j] = temp;
            }
        }
    }

    cout << "after sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
}

int main(int argc, char const *argv[])
{
    int a[10] = {8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
    List<int> arr(10, a);
    shellSortEnhanced(arr);
}
