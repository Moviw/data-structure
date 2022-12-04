#ifndef __STACK_H__
#define __STACK_H__
using namespace std;
template <class T>
class Stack
{
private:
    T *st;
    int top;
    size_t maxSize;

public:
    Stack(const int max = 100)
    {
        top = -1;
        maxSize = max;
        st = new T[maxSize];
    }
    ~Stack()
    {
        delete[] st;
    }
    void Show();
    void Clear();                          //变为空栈
    bool Push(const T item);               // item 入栈，成功则返回真, 否则返回假
    bool Pop(T &item);                     //返回栈顶内容并弹出,成功返回真,否则返回假
    bool TopValue(T &item);                //返回栈顶内容但不弹出,成功返回真,否则返回假
    bool IsEmpty() { return (top == -1); } // 若栈已空返回真
    bool IsFull();                         //若栈已满返回真
    int GetSize();                         //返回栈内元素个数
};
#endif

template <class T>
void Stack<T>::Clear() //变为空栈
{
    while (top != -1)
    {
        st[top--] = 0;
    }
}

template <class T>
bool Stack<T>::Push(const T item) // item 入栈，成功则返回真, 否则返回假
{
    if (top == maxSize - 1)
    {
        cout << "满了别往里放了\n";
        return false;
    }
    top++;
    st[top] = item;
    return false;
}

template <class T>
void Stack<T>::Show()
{
    int i = 0;
    while (i <= top)
    {
        cout << "this is : " << st[i++] << endl;
    }
}

template <class T>
bool Stack<T>::TopValue(T &item) //返回栈顶内容但不弹出,成功返回真,否则返回假
{
    if (top == -1)
    {
        cout << "里面没东西\n";
        return false;
    }
    item = st[top];
    return true;
}
template <class T>
bool Stack<T>::Pop(T &item) //返回栈顶内容并弹出,成功返回真,否则返回假
{
    if (top == -1)
    {
        cout << "里面没东西\n";
        return false;
    }
    item = st[top];
    top--;
    return true;
}

template <class T>
int Stack<T>::GetSize()
{
    return top;
}
