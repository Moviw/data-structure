#include <iostream>
using namespace std;
#include "List.h"
int main()
{
    List<int> a(20);
    a.Append(20);
    a.Insert(6, 77);
    a.Remove(4);
    a.SortedInsert(24);
    a.Show();
    // a.advanced_delete(0, 7);

    List<int> b(20);
    b.Append(33);
    b.Append(77);
    b.Show();

    List<int> temp(20);
    temp = a.Merge(b);
    temp.Show();
    return 0;
}
