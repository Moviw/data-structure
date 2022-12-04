#ifndef __MINHEAP_H__
#define __MINHEAP_H__

#include <iostream>
using namespace std;

template <class T>
class MinHeap
{
private:
    T *heapArray;     //存放堆数据的数组
    int CurrentSize;  //当前堆中元素数目
    int MaxSize;      //堆所能容纳的最大元素数目
    void BuildHeap(); //建堆
public:
    MinHeap(const int n); // n为堆的最大元素数目
    virtual ~MinHeap() { delete[] heapArray; };
    bool isLeaf(int pos) const;                          // pos位置上的元素是否是叶子节点
    int leftchild(int pos) const { return 2 * pos + 1; } //返回该位置的左孩子的索引

    int rightchild(int pos) const { return 2 * pos + 1; } //返回该位置的右孩子的索引
    int parent(int pos) const { return (pos - 1) / 2; }   //返回该位置的父节点的索引
    bool Remove(int pos, T &node);                        //删除给定下标的元素 返回给node
    bool Insert(const T &newNode);                        //向堆中插入新元素newNode
    T &RemoveMin();                                       //从堆顶删除最小值
    void SiftUp(int position);                            //从position开始向上调整
    void SiftDown(int left);                              //从left开始向下筛选
};

template <class T>
MinHeap<T>::MinHeap(const int n)
{
    if (n <= 0)
        return;
    CurrentSize = 0;
    MaxSize = n;                //初始化堆容量为n
    heapArray = new T[MaxSize]; //创建堆空间
    BuildHeap();                //此处进行堆元素的赋值工作
}

template <class T>
bool MinHeap<T>::isLeaf(int pos) const
{
    return (pos >= CurrentSize / 2) && (pos < CurrentSize);
}

template <class T>
void MinHeap<T>::SiftDown(int position)
{
    int i = position;       //标识父结点
    int j = 2 * i + 1;      //标识关键值较小的子结点
    T temp = heapArray[i];  //保存父结点
    while (j < CurrentSize) //过筛
    {
        if ((j < CurrentSize - 1) && (heapArray[j] > heapArray[j + 1]))
            j++; // j指向数值较小的子结点
        if (temp > heapArray[j])
        {
            heapArray[i] = heapArray[j];
            i = j;
            j = 2 * j + 1; //向下继续
        }
        else
            break;
    }
    heapArray[i] = temp;
}

template <class T>
void MinHeap<T>::BuildHeap()
{
    for (int i = CurrentSize / 2 - 1; i >= 0; i--)
        SiftDown(i); //反复调用筛选函数
}

template <class T>
bool MinHeap<T>::Insert(const T &newNode) //向堆中插入新元素newNode
{
    if (CurrentSize == MaxSize) //堆空间已经满
    {
        cout << "满了 没地放了\n"
             << endl;
        return false;
    }
    heapArray[CurrentSize] = newNode;
    SiftUp(CurrentSize); //向上调整
    CurrentSize++;
    return true;
}

template <class T>
void MinHeap<T>::SiftUp(int position) //从position开始调整，使序列成为堆
{
    int temppos = position;
    T temp = heapArray[temppos];
    while ((temppos > 0) && (heapArray[parent(temppos)] > temp))
    {
        heapArray[temppos] = heapArray[parent(temppos)];
        temppos = parent(temppos);
    }
    heapArray[temppos] = temp;
}

template <class T>
T &MinHeap<T>::RemoveMin()
{
    if (CurrentSize == 0)
    {
        cout << "没东西了 没法删";
        return;
    }
    else
    {
        swap(0, --CurrentSize); //交换堆顶和堆尾的元素
        if (CurrentSize > 1)
            SiftDown(0);
        return heapArray[CurrentSize];
    }
}

template <class T>
bool MinHeap<T>::Remove(int pos, T &node)
{
    if ((pos < 0) || (pos >= CurrentSize))
        return false;
    node = heapArray[pos];
    heapArray[pos] = heapArray[--CurrentSize];
    if (heapArray[parent(pos)] > heapArray[pos])
        SiftUp(pos);
    else
        SiftDown(pos);
    return true;
}

#endif