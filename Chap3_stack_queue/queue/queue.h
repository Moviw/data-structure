#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    int mSize; //存放队列的数组的大小
    int front; //表示队头所在位置的下标
    int rear;  //表示队尾所在位置的下标
    T *List;   //存放类型为T的队列元素的数组
public:
    Queue(int size = 20)
    {
        mSize = size + 1; //浪费一个存储空间，以区别队列空和队列满
        List = new T[mSize];
        front = 0;
        rear = 0;
    }
    ~Queue()
    {
        delete[] List;
    }
    void Clear();                            //清空队列
    bool EnQueue(const T item);              // item 入队 插入队尾
    bool DeQueue(T &item);                   //返回队首元素并从队列中删除
    bool GetFront(T &item);                  //返回队首元素，但不删除
    bool IsEmpty() { return front == rear; } //判断是否为空
    void Show();
};

template <class T>
void Queue<T>::Clear() //清空队列
{
    front = rear;
}

template <class T>
bool Queue<T>::EnQueue(const T item) // item 入队 插入队尾
{
    if ((rear + 1) % mSize == front)
    {
        cout << "满了别放了\n";
        return false;
    }
    List[rear] = item;
    rear = (rear + 1) % mSize;
    return true;
}

template <class T>
bool Queue<T>::DeQueue(T &item) //返回队首元素并从队列中删除
{
    if (front == rear)
    {
        cout << "啥也没有\n";
        return false;
    }
    item = List[front];
    front = (front + 1) % mSize;
    return true;
}

template <class T>
bool Queue<T>::GetFront(T &item) //返回队首元素，但不删除
{

    if (front == rear)
    {
        cout << "啥也没有\n";
        return false;
    }
    item = List[front];
    return true;
}

template <class T>
void Queue<T>::Show()
{
    int a = front;
    int b = rear;
    while (a % mSize != b)
    {
        cout << List[a++] << endl;
    }
    cout << "the end\n";
}
#endif
