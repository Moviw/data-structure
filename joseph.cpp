#include <iostream>
#include "Chap2_linear_list/List/List.h"

using namespace std;

template <class T>
int jos(int n, int m, int s = 0)
{
    List<T> ret = List<T>(n);
    int pos = s;
    while (ret.length() > 1)
    {
        int temp = 1;
        while (temp < m)
        {
            temp++;
            pos = (++pos) % ret.length();
        }
        int del;
        ret.getValue(pos, del);
        cout << "be removed one is : " << del << " at [" << pos << "]" << endl;
        cout<<del<<" ";
    }
    int final;
    ret.getValue(pos, final);
    cout<<final<<" ";
    return final;
}

int main()
{
    int n = 10, s = 1, m = 2;
    int a = jos<int>(n, m, s);
    cout << "the last is : " << a << endl;

}