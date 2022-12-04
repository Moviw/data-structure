#include <iostream>
#include "Linked_List.h"
using namespace std;

int main()
{
    Linked_List<int> a;
    a.Append(7);
    a.Append(2);
    a.Append(4);
    a.Append(93);
    a.Insert(3, 3880);
    a.AscendSort();
    a.Show();
    // a.advanced_delete(5,99);

    Linked_List<int> x;
    x.Append(3);
    x.Append(4);
    x.Append(5);
    x.Append(6);
    x.Append(7);
    x.Append(8);
    x.Append(9);
    x.Append(10);
    x.Show();
    Linked_List<int> temp = a.Contact(x);
    temp.Show();
}