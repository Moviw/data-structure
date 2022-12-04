#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include <iostream>
using namespace std;

//节点类
template <class T>
class Link
{
public:
    T data;
    Link<T> *next;

    Link(const T info, Link<T> *nextValue = nullptr)
    {
        data = info;
        next = nextValue;
    }
    Link(Link<T> *nextvalue = nullptr)
    {
        next = nextvalue;
    }
};

template <class T>
class Linked_List
{
private:
    Link<T> *head;
    T GetValue(const int pos);                   //根据位置查找值
    void SetValue(const int pos, const T value); //根据位置修改值

public:
    Linked_List();
    Linked_List &operator=(Linked_List &x)
    {
        this->head = x.head;
    }
    void Clear();
    bool IsEmpty();                                    //链表为空时 返回True
    int Length();                                      //返回此链表的当前实际长度
    void Show();                                       //打印该链表
    void Append(const T value);                        //在表尾添加一个元素value,表的长度增1
    bool Insert(const int pos, const T value);         //在位置p上插入一个元素value,表的长度增1
    bool Remove(const int pos);                        //删除位置p上的元素,表的长度减1
    void AscendSort(bool flag = true);                 //按顺序排类，默认为升序,flag=false时为降序
    void AdvancedDelete(const int min, const int max); //习题3
    bool IsNull(const int pos);                        //根据是第几个元素确定是否为空
    Linked_List<T> &Contact(Linked_List<T> &x);        //习题4
    Link<T> *GetHead() { return head; }
};
#endif

template <class T>
bool Linked_List<T>::IsNull(const int pos)
{
    Link<T> *p = head->next;
    int i = 0;
    while (i < pos)
    {
        i++;
        p = p->next;
    }
    return (p == nullptr);
}
template <class T>
T Linked_List<T>::GetValue(const int pos) //根据位置查找值
{
    int i = 0;
    Link<T> *p = head->next;
    while (i < pos)
    {
        p = p->next;
        i++;
    }
    return p->data;
}

template <class T>
void Linked_List<T>::SetValue(const int pos, const T value) //根据位置查找值
{
    int i = 0;
    Link<T> *p = head->next;
    while (i < pos)
    {
        p = p->next;
        i++;
    }
    p->data = value;
}

template <class T>
Linked_List<T>::Linked_List()
{
    head = new Link<T>();
    // tail = new Link<T>;
}

template <class T>
void Linked_List<T>::Append(const T value) //在表尾添加一个元素value,表的长度增1
{
    Link<T> *new_one = new Link<T>(value);
    Link<T> *p = this->head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    p->next = new_one;
}

template <class T>
void Linked_List<T>::Show()
{
    Link<T> *p = head->next;
    while (p != nullptr)
    {
        cout << p->data << "  ";
        p = p->next;
    }
    cout << endl;
}

template <class T>
int Linked_List<T>::Length() //在表尾添加一个元素value,表的长度增1
{
    Link<T> *p = head->next;
    int i = 0;
    while (p != nullptr)
    {
        p = p->next;
        i++;
    }
    return i;
}

template <class T>
bool Linked_List<T>::Insert(const int pos, const T value) //在位置p上插入一个元素value,表的长度增1
{
    if (pos < 0 || pos > this->Length())
    {
        cout << "p不对，太大或太小\n";
        return false;
    }
    Link<T> *new_one = new Link<T>(value);
    int i = 0;
    Link<T> *p = head;
    Link<T> *q = p->next;
    while (i < pos)
    {
        p = p->next;
        q = q->next;
        i++;
    }
    p->next = new_one;
    new_one->next = q;
    return true;
}
template <class T>
bool Linked_List<T>::Remove(const int pos) //删除位置p上的元素,表的长度减 1
{
    if (pos < 0 || pos >= this->Length())
    {
        cout << "p不对，太大或太小\n";
        return false;
    }
    int i = 0;
    Link<T> *p = head;
    Link<T> *q = p->next;
    while (i < pos)
    {
        p = p->next;
        q = q->next;
        i++;
    }
    p->next = q->next;
    free(q);
    return true;
}

template <class T>
void Linked_List<T>::AscendSort(bool flag) //按顺序排类，默认为升序,flag=false时为降序
{
    if (flag) //升序排列
    {
        for (int i = Length() - 1; i > 1; --i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (GetValue(j) > GetValue(j + 1))
                {
                    int tmp = GetValue(j);
                    SetValue(j, GetValue(j + 1));
                    SetValue(j + 1, tmp);
                }
            }
        }
    }
    else //降序排列
    {
        for (int i = Length() - 1; i >= 1; --i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (GetValue(j) < GetValue(j + 1))
                {
                    int tmp = GetValue(j);
                    SetValue(j, GetValue(j + 1));
                    SetValue(j + 1, tmp);
                }
            }
        }
    }
}
template <class T>
void Linked_List<T>::AdvancedDelete(const int min, const int max) //习题3
{
    Link<T> *p = head;
    int i = 0;
    while (p->next != nullptr)
    {
        if (p->next->data > min && p->next->data < max)
        {
            Remove(i);
        }
        else
        {
            i++;
            p = p->next;
        }
    }
}

template <class T>
Linked_List<T> &Linked_List<T>::Contact(Linked_List<T> &x) //习题4
{
    Linked_List<T> *temp = new Linked_List<T>();
    this->AscendSort(false);
    x.AscendSort(false);
    int i = 0, j = 0;
    int all = this->Length() + x.Length();
    while (i + j < all)
    {
        if (this == nullptr)
        {
            temp->Append(x.GetValue(j));
            j++;
            continue;
        }
        if (x.IsNull(j))
        {
            temp->Append(this->GetValue(i));
            i++;
            continue;
        }
        if (this->GetValue(i) > x.GetValue(j))
        {
            temp->Append(this->GetValue(i));
            i++;
        }
        else
        {
            temp->Append(x.GetValue(j));
            j++;
        }
    }
    return *temp;
}