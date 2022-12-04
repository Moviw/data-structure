
#ifndef __LIST_H__
#define __LIST_H__
using namespace std;
template <class T>
//假定顺序表的元素类型为T
class List
{
    // 顺序表,向量
private:
    T *aList;    //私有变量,存储顺序表的实例
    int maxSize; //顺序表最大长度
    int curLen;  //顺序表当前长度
public:
    List(const int size)
    {
        //创建一个新的顺序表，参数为表实例的最大长度
        maxSize = size;
        aList = new T[maxSize];

        curLen = maxSize;
    }
    List(const int size, int *arr)
    {
        //创建一个新的顺序表，参数为表实例的最大长度
        maxSize = size;
        aList = new T[maxSize];
        for (int i = 0; i < maxSize; i++)
        {
            aList[i] = arr[i];
        }
        curLen = maxSize;
    }
    List<T> operator=(const List<T> &x)
    {
        this->maxSize = x.maxSize;
        this->curLen = x.curLen;
        delete[] aList;
        aList = new T[maxSize];
        memcpy(aList, x.aList, sizeof(T) * maxSize);
    }
    ~List()
    {
        // 析构函数,用于消除该表实例
        delete[] aList;
    }
    void Clear()
    {
        //将顺序表存储的内容清除,成为空表
        delete[] aList;
        curLen = 0;
        aList = new T[maxSize];
    }
    bool IsEmpty() //线性表为空时 返回True
    {
        return !curLen;
    }
    int Length() { return this->curLen; } //返回此顺序表的当前实际长度
    inline int GetLen() { return this->curLen; }
    void Show();                               //打印顺序表
    bool Append(const T value);                //在表尾添加一个元素value,表的长度增Ⅰ
    bool Insert(const int pos, const T value); //在位置p上插入一个元素value,表的长度增Ⅰ
    bool Remove(const int pos);                //删除位置p上的元素,表的长度减 1
    bool SetValue(const int p, const T value); //用value修改位置p的元素值
    bool GetValue(const int p, T &value);      //把位置p的元素值返回到变量value中
    bool GetPos(int &p, const T value);        //查找值为 value 的元素，并返回第1次出现的位置
    T &operator[](int n) const
    {
        if (n >= curLen)
        {
            cout << "array index out of bound return the last one...\n";
            return aList[curLen - 1];
        }
        return aList[n];
    }
    bool SortedInsert(const T value);              // 习题1
    void AdvancedDelete(const int i, const int k); //习题6
    List<T> Merge(List<T> &x);                     //习题8
};

template <class T>
bool List<T>::SortedInsert(const T value)
{
    if (curLen >= maxSize)
    {
        cout << "满了没地了\n";
        return false;
    }
    else
    {
        int i = 0;
        while (i < curLen)
        {
            if (value >= aList[i])
            {
                i++;
            }
            else
            {
                break;
            }
        }
        for (int temp = curLen; temp > i; temp--)
        {
            aList[temp] = aList[temp - 1];
        }
        aList[i] = value;
        curLen++;
        return true;
    }
}
template <class T>
void List<T>::Show() //打印顺序表
{
    for (int i = 0; i < curLen; i++)
    {
        cout << "aList[" << i << "] : " << aList[i] << endl;
    }
    cout << endl;
}

template <class T>
bool List<T>::Append(const T value) //在表尾添加一个元素value,表的长度增Ⅰ
{
    if (curLen > maxSize - 1)
    {
        cout << "不行 因为已经满了\n";
        return false;
    }
    else
    {
        curLen++;
        aList[curLen - 1] = value;
        return true;
    }
}

template <class T>
bool List<T>::Insert(const int p, const T value) //在位置p上插入一个元素value,表的长度增1
{
    if (curLen > maxSize - 1)
    {
        cout << "不行 因为已经满了\n";
        return false;
    }
    else if (p < 0 || p > curLen)
    {
        cout << "输入的p有误\n";
        return false;
    }
    else
    {
        for (int i = curLen - 1; i >= p; i--)
        {
            aList[i + 1] = aList[i];
        }
        curLen++;
        aList[p] = value;
        return true;
    }
}

template <class T>
bool List<T>::SetValue(const int p, const T value) //用value修改位置p的元素值
{
    if (p < 0 || p > curLen)
    {
        cout << "输入的p有误\n";
        return false;
    }
    else
    {
        aList[p] = value;
        return true;
    }
}

template <class T>
bool List<T>::GetValue(const int p, T &value) //把位置p的元素值返回到变量value中
{
    if (p < 0 || p > curLen)
    {
        cout << "输入的p有误\n";
        return false;
    }
    else
    {
        value = aList[p];
        return true;
    }
}

template <class T>
bool List<T>::GetPos(int &p, const T value) //查找值为 value 的元素，并返回第1次出现的位置
{
    bool flag = 0;
    for (int i = 0; i < curLen; i++)
    {
        if (aList[i] == value)
        {
            p = i;
            flag = 1;
        }
    }
    return flag;
}

template <class T>
bool List<T>::Remove(const int p) //删除位置p上的元素,表的长度减 1
{
    if (curLen == 0)
    {
        cout << "不行 没得可删了\n";
        return false;
    }
    else if (p < 0 || p > curLen - 1)
    {
        cout << "输入的p有误\n";
        return false;
    }
    else
    {
        for (int i = p; i < curLen - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
    }
    curLen--;
    return true;
}

template <class T>
void List<T>::AdvancedDelete(const int i, const int k) //习题6
{
    if (i < 0 || i >= curLen)
    {
        cout << "i的值太大或太小了\n";
        return;
    }
    else if (k < 0)
    {
        cout << "k的值不能是负数\n";
        return;
    }
    else if (i + k > curLen)
    {
        cout << "你要删的元素太多了都超出我目前有的了\n";
        return;
    }
    for (int temp = i; temp < i + k; temp++)
    {
        Remove(i);
    }
}

template <class T>
List<T> List<T>::Merge(List<T> &x) //习题8
{
    List<T> temp(40);
    int a1 = this->GetLen();
    int a2 = x.GetLen();
    for (int i = 0; i < a2; i++)
    {
        for (int j = 0; j < a1; j++)
        {
            if (aList[i] == aList[j])
            {
                temp.Append(aList[i]);
                break;
            }
        }
    }
    return temp;
}

#endif