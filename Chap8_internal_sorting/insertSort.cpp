#include <iostream>
#include "C:\Users\19735\Desktop\SJJG\Chap2_linear_list/List/List.h"
using namespace std;

/*
    插入排序基本思想:
        每步将一个待排序的对象按照其关键码的大小，插入到前面已经排好序的一组对象的适当位置上，直到对象全部插入为止

        即边插入边排序，保证子序列中随时都是排好序的

    按照定位插入位置的方法分类为:
    按顺序法定位插入位置 -> 直接插入排序
    按二分法定位插入位置 -> 二分插入排序
    缩小增量多遍插入排序 -> 希尔排序
*/

/*
    直接插入排序步骤:
        1. 复制插入元素 x=a[i];
        2. 记录后移 查找插入位置
*/
void insertSort(List<int> arr)
{
    cout << "before sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;

    for (int i = 1; i < arr.getLen(); i++) // 从第二个开始 因为一个元素已经是一个有序数组了
    {
        int insertVal = arr[i];  //待插入的数
        int insertIndex = i - 1; //待输入的位置

        /*
            1. insertIndex>=0保证在给insertVal找插入位置是不越界
            2. insertVal < arr[insertIndex]则表示待插入的数还没有找到插入位置
            3. 进入循环将insertIndex左移
        */
        while (insertIndex >= 0 && insertVal < arr[insertIndex])
        {
            arr[insertIndex + 1] = arr[insertIndex];
            insertIndex--;
        }
        arr[insertIndex + 1] = insertVal;
    }

    cout << "after sorting :" << endl
         << endl;
    arr.Show();
    cout << endl;
}
